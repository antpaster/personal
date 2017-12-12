package com.example.apasternak.mediastoreexample;

import java.io.BufferedInputStream;
import java.io.FileInputStream;
import java.io.FileNotFoundException;
import java.io.IOException;

import android.app.Activity;
import android.content.Intent;
import android.content.pm.PackageManager;
import android.graphics.Bitmap;
import android.graphics.BitmapFactory;
import android.net.Uri;
import android.os.Bundle;
import android.os.StrictMode;
import android.provider.MediaStore;
import android.view.View;
import android.widget.Button;
import android.widget.ImageView;
import android.widget.Toast;
import android.widget.VideoView;

public class MainActivity extends Activity {

    // Activity request codes
    private static final int CAMERA_CAPTURE_IMAGE_REQUEST_CODE = 100;
    private static final int CAMERA_CAPTURE_VIDEO_REQUEST_CODE = 200;
//    public static final int MEDIA_TYPE_IMAGE = 1;
//    public static final int MEDIA_TYPE_VIDEO = 2;

    private CaptionService mCaptionService;

    private boolean mIsServiceStarted;

    private Uri mFileUri; // file url to store image/video

    private Intent mIntent = null;

    private ImageView mImagePreview;
    private VideoView mVideoPreview;
    private Button mBtnCapturePicture, mBtnRecordVideo;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        StrictMode.VmPolicy.Builder builder = new StrictMode.VmPolicy.Builder();
        StrictMode.setVmPolicy(builder.build());

//        mCaptionService = new CaptionService();
        mIntent = new Intent(this, CaptionService.class);

        mImagePreview = (ImageView) findViewById(R.id.imgPreview);
        mVideoPreview = (VideoView) findViewById(R.id.videoPreview);
        mBtnCapturePicture = (Button) findViewById(R.id.btnCapturePicture);
        mBtnRecordVideo = (Button) findViewById(R.id.btnRecordVideo);

        mIsServiceStarted = false;

        /**
         * Capture image button click event
         */
        mBtnCapturePicture.setOnClickListener(new View.OnClickListener() {

            @Override
            public void onClick(View v) {
                // capture picture
//                captureImage();
            }
        });

        /**
         * Record video button click event
         */
        mBtnRecordVideo.setOnClickListener(new View.OnClickListener() {

            @Override
            public void onClick(View v) {
                // record video
                startService(mIntent);
                mIsServiceStarted = true;
//                recordVideo();
            }
        });

        // Checking camera availability
        if (!isDeviceSupportCamera()) {
            Toast.makeText(getApplicationContext(),
                    "Sorry! Your device doesn't support camera",
                    Toast.LENGTH_LONG).show();
            // will close the app if the device does't have camera
            finish();
        }
    }

    /**
     * Checking device has camera hardware or not
     * */
    private boolean isDeviceSupportCamera() {
        if (getApplicationContext().getPackageManager().hasSystemFeature(
                PackageManager.FEATURE_CAMERA)) {
            // this device has a camera
            return true;
        } else {
            // no camera on this device
            return false;
        }
    }

//    /**
//     * Capturing Camera Image will lauch camera app requrest image capture
//     */
//    private void captureImage() {
//        Intent intent = new Intent(MediaStore.ACTION_IMAGE_CAPTURE);
//
//        mFileUri = getOutputMediaFileUri(MEDIA_TYPE_IMAGE);
//
//        intent.putExtra(MediaStore.EXTRA_OUTPUT, mFileUri);
//
//        // start the image capture Intent
//        startActivityForResult(intent, CAMERA_CAPTURE_IMAGE_REQUEST_CODE);
//    }

    /**
     * Here we store the file url as it will be null after returning from camera
     * app
     */
    @Override
    protected void onSaveInstanceState(Bundle outState) {
        super.onSaveInstanceState(outState);

        // save file url in bundle as it will be null on screen orientation
        // changes
        if (mIsServiceStarted) {
            mFileUri = mIntent.getParcelableExtra(MediaStore.EXTRA_OUTPUT);
            outState.putParcelable("file_uri", mFileUri);
        }
    }

    @Override
    protected void onRestoreInstanceState(Bundle savedInstanceState) {
        super.onRestoreInstanceState(savedInstanceState);

        // get the file url
        if (mIsServiceStarted) {
            mFileUri = mIntent.getParcelableExtra(MediaStore.EXTRA_OUTPUT);
            mFileUri = savedInstanceState.getParcelable("file_uri");
        }
    }

//    /**
//     * Recording video
//     */
//    private void recordVideo() {
//        Intent intent = new Intent(MediaStore.ACTION_VIDEO_CAPTURE);
//
//        mFileUri = getOutputMediaFileUri(MEDIA_TYPE_VIDEO);
//
//        // set video quality
//        intent.putExtra(MediaStore.EXTRA_VIDEO_QUALITY, 1);
//
//        intent.putExtra(MediaStore.EXTRA_OUTPUT, mFileUri); // set the image file
//        // name
//
//        // start the video capture Intent
//        startActivityForResult(intent, CAMERA_CAPTURE_VIDEO_REQUEST_CODE);
//    }

    /**
     * Receiving activity result method will be called after closing the camera
     * */
    @Override
    protected void onActivityResult(int requestCode, int resultCode, Intent data) {
        // if the result is capturing Image
        if (requestCode == CAMERA_CAPTURE_IMAGE_REQUEST_CODE) {
            if (resultCode == RESULT_OK) {
                // successfully captured the image
                // display it in image view
                previewCapturedImage();
            } else if (resultCode == RESULT_CANCELED) {
                // user cancelled Image capture
                Toast.makeText(getApplicationContext(),
                        "User cancelled image capture", Toast.LENGTH_SHORT)
                        .show();
            } else {
                // failed to capture image
                Toast.makeText(getApplicationContext(),
                        "Sorry! Failed to capture image", Toast.LENGTH_SHORT)
                        .show();
            }
        } else if (requestCode == CAMERA_CAPTURE_VIDEO_REQUEST_CODE) {
            if (resultCode == RESULT_OK) {
                // video successfully recorded
                // preview the recorded video
                previewVideo();
            } else if (resultCode == RESULT_CANCELED) {
                // user cancelled recording
                Toast.makeText(getApplicationContext(),
                        "User cancelled video recording", Toast.LENGTH_SHORT)
                        .show();
            } else {
                // failed to record video
                Toast.makeText(getApplicationContext(),
                        "Sorry! Failed to record video", Toast.LENGTH_SHORT)
                        .show();
            }
        }
    }

    /**
     * Display image from a path to ImageView
     */
    private void previewCapturedImage() {
        try {
            // hide video preview
            mVideoPreview.setVisibility(View.GONE);

            stopService(mIntent);

            mImagePreview.setVisibility(View.VISIBLE);

//            mImagePreview.setImageURI(mFileUri);

//            // bitmap factory
//            BitmapFactory.Options options = new BitmapFactory.Options();
//
//            // downsizing image as it throws OutOfMemory Exception for larger
//            // images
//            options.inSampleSize = 8;
//
//            final Bitmap bitmap = BitmapFactory.decodeFile(mFileUri.getPath(),
//                    null);

            if (mIsServiceStarted) {
                mFileUri = mIntent.getParcelableExtra(MediaStore.EXTRA_OUTPUT);
                FileInputStream fis = new FileInputStream(mFileUri.getPath());
                BufferedInputStream bis = new BufferedInputStream(fis);
                byte[] bytes = new byte[bis.available()];
                bis.read(bytes);

                Bitmap bitmap = BitmapFactory.decodeByteArray(bytes, 0, bytes.length);
                mImagePreview.setImageBitmap(bitmap);
            }
        } catch (NullPointerException e) {
            e.printStackTrace();
        } catch (FileNotFoundException e) {
            e.printStackTrace();
        } catch (IOException e) {
            e.printStackTrace();
        }
    }

    /**
     * Previewing recorded video
     */
    private void previewVideo() {
        try {
            // hide image preview
            mImagePreview.setVisibility(View.GONE);

            mVideoPreview.setVisibility(View.VISIBLE);

            if (mIsServiceStarted) {
                mFileUri = mIntent.getParcelableExtra(MediaStore.EXTRA_OUTPUT);
                mVideoPreview.setVideoPath(mFileUri.getPath());
                // start playing
                mVideoPreview.start();
            }
        } catch (Exception e) {
            e.printStackTrace();
        }
    }

    /**
     * ------------ Helper Methods ----------------------
     * */

//    /**
//     * Creating file uri to store image/video
//     */
//    public Uri getOutputMediaFileUri(int type) {
////        return FileProvider.getUriForFile(getApplicationContext(),
////                getApplicationContext().getPackageName() + ".my.package.provider",
////                getOutputMediaFile(type));
//
//        return Uri.fromFile(getOutputMediaFile(type));
//    }

//    /**
//     * returning image / video
//     */
//    private File getOutputMediaFile(int type) {
//        // External sdcard location
//        File mediaStorageDir = new File(
//                getApplicationContext().getExternalFilesDir(null).getAbsolutePath());
//
////        File mediaStorageDir = new File(Environment.getExternalStorageDirectory()
////                /*Environment.getExternalStoragePublicDirectory(
////                Environment.DIRECTORY_PICTURES)*/.getAbsolutePath()/*, IMAGE_DIRECTORY_NAME*/);
//
////        File mediaStorageDir = new File(Environment.getExternalStoragePublicDirectory(
////                Environment.DIRECTORY_PICTURES), IMAGE_DIRECTORY_NAME);
//
//        // Create the storage directory if it does not exist
//        if (!mediaStorageDir.exists()) {
//            if (!mediaStorageDir.mkdirs()) {
//                Log.d(IMAGE_DIRECTORY_NAME, "Oops! Failed create "
//                        + IMAGE_DIRECTORY_NAME + " directory");
//                return null;
//            }
//        }
//
//        // Create a media file name
//        String timeStamp = new SimpleDateFormat("yyyyMMdd_HHmmss",
//                Locale.getDefault()).format(new Date());
//
//        File mediaFile;
//        if (type == MEDIA_TYPE_IMAGE) {
//            mediaFile = new File(mediaStorageDir.getPath() + File.separator + "IMG_"
//                    + timeStamp + ".jpg");
//        } else if (type == MEDIA_TYPE_VIDEO) {
//            mediaFile = new File(mediaStorageDir.getPath() + File.separator + "VID_"
//                    + timeStamp + ".mp4");
//        } else {
//            return null;
//        }
//
//        return mediaFile;
//    }
}
