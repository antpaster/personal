package com.example.apasternak.textureviewtransform;

import java.io.File;
import java.io.FileNotFoundException;
import java.io.FileOutputStream;
import java.io.IOException;
import java.io.OutputStream;

import android.annotation.SuppressLint;
import android.content.Intent;
import android.database.Cursor;
import android.graphics.Bitmap;
import android.graphics.BitmapFactory;
import android.graphics.Canvas;
import android.graphics.Color;
import android.graphics.Paint;
import android.graphics.Rect;
import android.graphics.drawable.Drawable;
import android.net.Uri;
import android.os.Bundle;

import android.os.Environment;
import android.provider.MediaStore;
import android.support.v4.content.ContextCompat;
import android.support.v7.app.AppCompatActivity;
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

//                String pathLink = Environment.getExternalStorageDirectory() + File.separator + "testing.jpg";
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
}
