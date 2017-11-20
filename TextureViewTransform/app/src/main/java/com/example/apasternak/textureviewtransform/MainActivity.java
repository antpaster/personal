package com.example.apasternak.textureviewtransform;

import java.io.File;
import java.io.FileNotFoundException;
import java.io.FileOutputStream;
import java.io.IOException;
import java.io.OutputStream;
import java.nio.ByteBuffer;
import java.util.ArrayList;
import java.util.List;
import java.util.concurrent.Semaphore;

import android.annotation.SuppressLint;
import android.app.Activity;
import android.content.Context;
import android.content.Intent;
import android.graphics.Bitmap;
import android.graphics.BitmapFactory;
import android.graphics.Canvas;
import android.graphics.Color;
import android.graphics.ImageFormat;
import android.graphics.Paint;
import android.graphics.Rect;
import android.graphics.drawable.Drawable;
import android.hardware.camera2.CameraAccessException;
import android.hardware.camera2.CameraCharacteristics;
import android.hardware.camera2.CameraDevice;
import android.hardware.camera2.CameraManager;
import android.hardware.camera2.CameraMetadata;
import android.hardware.camera2.CaptureRequest;
import android.media.Image;
import android.media.ImageReader;
import android.net.Uri;
import android.os.Bundle;

import android.os.Environment;
import android.os.Handler;
import android.provider.MediaStore;
import android.support.annotation.NonNull;
import android.util.Size;
import android.support.v7.app.AppCompatActivity;
import android.util.SparseIntArray;
import android.view.Surface;
import android.view.TextureView;
import android.view.View;
import android.widget.ImageButton;
import android.widget.ImageView;
import android.widget.Toast;

public class MainActivity extends AppCompatActivity {

    ImageButton mInsertImageButton;
    ImageButton mSaveImageButton;
    String mStringForDrawing = "Hello, world!";
    final int RESULT_LOAD_IMAGE = 20;
    String mImagePath = "";
    ImageView mImageView;

    @SuppressLint("NewApi")
    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        mTextureView = findViewById(R.id.textureView);
        mImageView = findViewById(R.id.imageView);

        mInsertImageButton = findViewById(R.id.insert);
        mInsertImageButton.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {

                Drawable drawable = /*ContextCompat.getDrawable(getApplicationContext(),
                        R.drawable.iss);*/
                        getResources().getDrawable(R.drawable.iss);
                mImageView.setImageResource(R.drawable.iss);

//                Intent i = new Intent(Intent.ACTION_PICK, android.provider.MediaStore.Images.Media.EXTERNAL_CONTENT_URI);
//                startActivityForResult(i, RESULT_LOAD_IMAGE);
            }
        });

        mSaveImageButton = findViewById(R.id.save);
        mSaveImageButton.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                if (mStringForDrawing.equals("") || mStringForDrawing.isEmpty()) {
                    return;
                }

                Bitmap bm = ProcessingBitmap(mStringForDrawing);

                mImageView.setImageBitmap(bm);

                String pathLink = Environment.getExternalStorageDirectory() + File.separator + "testing.jpg";
                cameraImageCapture(pathLink);
//                storeImage(bm, pathLink);

                Toast.makeText(MainActivity.this, mStringForDrawing, Toast.LENGTH_LONG).show();
            }
        });
    }

    @Override
    protected void onActivityResult(int requestCode, int resultCode, Intent data) {
        super.onActivityResult(requestCode, resultCode, data);

        if (requestCode == RESULT_LOAD_IMAGE && resultCode == RESULT_OK) {
            pickedImage = data.getData();
//            String[] filePath = { MediaStore.Images.Media.DATA };
//            Cursor cursor = getContentResolver().query(pickedImage, filePath, null, null, null);
//            cursor.moveToFirst();

            Uri uri = data.getData();
            String imagePath = uri.getPath();

//            mImagePath = cursor.getString(cursor.getColumnIndex(filePath[0]));
            Drawable drawable = Drawable.createFromPath(imagePath);
            mImageView.setBackground(drawable);
        }
    }

    Uri pickedImage;

    Bitmap ProcessingBitmap(String captionString) {
        Bitmap bm1;
        Bitmap newBitmap = null;
//        try {
            Toast.makeText(MainActivity.this, "R.drawable.iss",
                    Toast.LENGTH_LONG).show();

//            bm1 = BitmapFactory.decodeStream(getContentResolver().openInputStream(pickedImage));
            bm1 = BitmapFactory.decodeResource(getResources(), R.drawable.iss);

            Bitmap.Config config = bm1.getConfig();
            if (config == null) {
                config = Bitmap.Config.ARGB_8888;
            }

            newBitmap = Bitmap.createBitmap(bm1.getWidth(), bm1.getHeight(), config);

            Canvas canvas = new Canvas(newBitmap);
            canvas.drawBitmap(bm1, 0, 0, null);

            Paint paintText = new Paint(Paint.ANTI_ALIAS_FLAG);
            paintText.setColor(Color.RED);

            float textSizePx = 100;
            paintText.setTextSize(textSizePx);
            paintText.setStyle(Paint.Style.FILL);
            paintText.setShadowLayer(10f, 10f, 10f, Color.BLACK);

            Rect textRect = new Rect();
            paintText.getTextBounds(captionString, 0, captionString.length(), textRect);

            if (textRect.width() >= (canvas.getWidth() - 4))
                paintText.setTextSize(20);

            int xPos = (canvas.getWidth() / 2) - 2;
            int yPos = (int) ((canvas.getHeight() / 2) - ((paintText.descent() + paintText.ascent())
                    / 2)) ;

            canvas.drawText(captionString, 0, textSizePx, paintText);
//        } catch (FileNotFoundException e) {
//            e.printStackTrace();
//        }
        return newBitmap;
    }

    void storeImage(Bitmap mBitmap, String path) {
        File file = new File(path);

        FileOutputStream fOut = null;
        try {
            fOut = new FileOutputStream(file);
        } catch (FileNotFoundException e) {
            e.printStackTrace();
        }

        mBitmap.compress(Bitmap.CompressFormat.JPEG, 85, fOut);
        try {
            fOut.flush();
        } catch (IOException e) {
            e.printStackTrace();
        }

        try {
            fOut.close();
        } catch (IOException e) {
            e.printStackTrace();
        }

        try {
            MediaStore.Images.Media.insertImage(getContentResolver(), file.getAbsolutePath(),
                    file.getName(), file.getName());
        } catch (FileNotFoundException e) {
            e.printStackTrace();
        }
    }

    CameraDevice mCameraDevice;
    TextureView mTextureView;
    private static final SparseIntArray DEFAULT_ORIENTATIONS = new SparseIntArray();

    static {
        DEFAULT_ORIENTATIONS.append(Surface.ROTATION_0, 90);
        DEFAULT_ORIENTATIONS.append(Surface.ROTATION_90, 0);
        DEFAULT_ORIENTATIONS.append(Surface.ROTATION_180, 270);
        DEFAULT_ORIENTATIONS.append(Surface.ROTATION_270, 180);
    }

    Handler mBackgroundHandler;

    Semaphore mCameraOpenCloseLock = new Semaphore(1);

    CameraDevice.StateCallback mStateCallback = new CameraDevice.StateCallback() {

        @Override
        public void onOpened(@NonNull CameraDevice cameraDevice) {
            mCameraDevice = cameraDevice;
            startPreview();
            mCameraOpenCloseLock.release();
            if (null != mTextureView) {
                configureTransform(mTextureView.getWidth(), mTextureView.getHeight());
            }
        }

        @Override
        public void onDisconnected(@NonNull CameraDevice cameraDevice) {
            mCameraOpenCloseLock.release();
            cameraDevice.close();
            mCameraDevice = null;
        }

        @Override
        public void onError(@NonNull CameraDevice cameraDevice, int error) {
            mCameraOpenCloseLock.release();
            cameraDevice.close();
            mCameraDevice = null;
            Activity activity = getActivity();
            if (null != activity) {
                activity.finish();
            }
        }

    };

    void cameraImageCapture(String path) {
        if (null == mCameraDevice || !mTextureView.isAvailable())
            return;

        Context context = getApplicationContext();
        CameraManager manager = (CameraManager) context.getSystemService(Context.CAMERA_SERVICE);
        
        try {
            String cameraId = manager.getCameraIdList()[0];
            CameraCharacteristics characteristics
                    = manager.getCameraCharacteristics(cameraId);
            Size[] jpegSizes = null;
            if (characteristics != null) {
                jpegSizes = characteristics.get(
                        CameraCharacteristics.SCALER_STREAM_CONFIGURATION_MAP).getOutputSizes(
                        ImageFormat.JPEG);
            }
            int width = 480; // 480x320
            int height = 320;
            if (jpegSizes != null && 0 < jpegSizes.length) {
                width = jpegSizes[0].getWidth();
                height = jpegSizes[0].getHeight();
            }
            
            ImageReader reader = ImageReader.newInstance(width, height, ImageFormat.JPEG, 1);
            List<Surface> outputSurfaces = new ArrayList<>(2);
            outputSurfaces.add(reader.getSurface());
            outputSurfaces.add(new Surface(mTextureView.getSurfaceTexture()));

            final CaptureRequest.Builder captureBuilder;
            try {
                captureBuilder
                        = mCameraDevice.createCaptureRequest(CameraDevice.TEMPLATE_STILL_CAPTURE);
                captureBuilder.addTarget(reader.getSurface());
                captureBuilder.set(CaptureRequest.CONTROL_MODE, CameraMetadata.CONTROL_MODE_AUTO);
                // Orientation
                int rotation
                        = ((Activity) context).getWindowManager().getDefaultDisplay().getRotation();
                captureBuilder.set(CaptureRequest.JPEG_ORIENTATION,
                        DEFAULT_ORIENTATIONS.get(rotation));
            } catch (CameraAccessException e) {
                e.printStackTrace();
            }

            final File file = new File(path);

            ImageReader.OnImageAvailableListener readerListener
                    = new ImageReader.OnImageAvailableListener() {
                @Override
                public void onImageAvailable(ImageReader reader) {
                    Image image = null;
                    try {
                        image = reader.acquireLatestImage();
                        ByteBuffer buffer = image.getPlanes()[0].getBuffer();
                        byte[] bytes = new byte[buffer.capacity()];
                        buffer.get(bytes);
                        save(bytes);
                    } catch (FileNotFoundException e) {
                        e.printStackTrace();
                    } catch (IOException e) {
                        e.printStackTrace();
                    } finally {
                        if (image != null) {
                            image.close();
                        }
                    }
                }

                private void save(byte[] bytes) throws IOException {
                    OutputStream output = null;
                    try {
                        output = new FileOutputStream(file);
                        output.write(bytes);
                    } finally {
                        if (null != output) {
                            output.close();
                        }
                    }
                }
            };
            reader.setOnImageAvailableListener(readerListener, mBackgroundHandler);
        } catch (CameraAccessException e) {
            e.printStackTrace();
        }
    }


}
