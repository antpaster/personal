package com.example.apasternak.videotoserver;

import android.Manifest;
import android.app.Activity;
import android.content.Intent;
import android.database.Cursor;
import android.media.MediaCodec;
import android.media.MediaFormat;
import android.net.Uri;
import android.os.Bundle;
import android.os.Environment;
import android.provider.MediaStore;
import android.support.annotation.NonNull;
import android.support.v7.app.AppCompatActivity;
import android.text.TextUtils;
import android.util.Log;
import android.view.Surface;
import android.view.View;
import android.widget.Button;
import android.widget.Toast;
import android.widget.VideoView;
import java.io.File;
import java.io.IOException;
import java.nio.ByteBuffer;
import java.util.List;
import okhttp3.MediaType;
import okhttp3.MultipartBody;
import okhttp3.RequestBody;
import pub.devrel.easypermissions.EasyPermissions;
import retrofit2.Call;
import retrofit2.Callback;
import retrofit2.Response;
import retrofit2.Retrofit;
import retrofit2.converter.gson.GsonConverterFactory;


public class VideoToServerActivity extends AppCompatActivity implements
    EasyPermissions.PermissionCallbacks {

    private static final String TAG = VideoToServerActivity.class.getSimpleName();
    private static final int REQUEST_VIDEO_CAPTURE = 300;
    private static final int READ_REQUEST_CODE = 200;
    private static final String SERVER_PATH = "";
    private Uri mUri;
    private String mPathToStoredVideo;
    private VideoView mDisplayRecordedVideo;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_video_to_server);

        mDisplayRecordedVideo = (VideoView) findViewById(R.id.video_display);

        Button captureVideoButton = (Button) findViewById(R.id.capture_video);

        captureVideoButton.setOnClickListener(new View.OnClickListener() {

            @Override
            public void onClick(View v) {
                Intent videoCaptureIntent = new Intent(MediaStore.ACTION_VIDEO_CAPTURE);
                if (videoCaptureIntent.resolveActivity(getPackageManager()) != null) {
                    startActivityForResult(videoCaptureIntent, REQUEST_VIDEO_CAPTURE);
                }
            }
        });
    }

    @Override
    protected void onActivityResult(int requestCode, int resultCode, Intent data) {
        if (resultCode == Activity.RESULT_OK && requestCode == REQUEST_VIDEO_CAPTURE) {
            mUri = data.getData();
            
            if (EasyPermissions.hasPermissions(VideoToServerActivity.this,
                android.Manifest.permission.READ_EXTERNAL_STORAGE)) {
                mDisplayRecordedVideo.setVideoURI(mUri);
                mDisplayRecordedVideo.start();

                mPathToStoredVideo = getRealPathFromURIPath(mUri, VideoToServerActivity.this);
                Log.d(TAG, "Recorded Video Path " + mPathToStoredVideo);

                /// Store the video to your server
                uploadVideoToServer(mPathToStoredVideo);
            } else {
                EasyPermissions.requestPermissions(VideoToServerActivity.this,
                    getString(R.string.read_file), READ_REQUEST_CODE,
                    Manifest.permission.READ_EXTERNAL_STORAGE);
            }
        }
    }

    private String getFileDestinationPath() {
        String generatedFilename = String.valueOf(System.currentTimeMillis());
        String filePathEnvironment
            = Environment.getExternalStoragePublicDirectory(Environment.DIRECTORY_DOWNLOADS).
            getAbsolutePath();

        File directoryFolder = new File(filePathEnvironment + "/video/");
        if (!directoryFolder.exists()) {
            directoryFolder.mkdir();
        }

        Log.d(TAG, "Full path " + filePathEnvironment + "/video/" + generatedFilename + ".mp4");
        return filePathEnvironment + "/video/" + generatedFilename + ".mp4";
    }

    @Override
    public void onRequestPermissionsResult(int requestCode, @NonNull String[] permissions,
        @NonNull int[] grantResults) {
        super.onRequestPermissionsResult(requestCode, permissions, grantResults);

        EasyPermissions.onRequestPermissionsResult(requestCode, permissions, grantResults,
            VideoToServerActivity.this);
    }

    @Override
    public void onPermissionsGranted(int requestCode, List<String> perms) {
        if (mUri != null) {
            if (EasyPermissions.hasPermissions(VideoToServerActivity.this,
                android.Manifest.permission.READ_EXTERNAL_STORAGE)) {
                mDisplayRecordedVideo.setVideoURI(mUri);
                mDisplayRecordedVideo.start();

                mPathToStoredVideo = getRealPathFromURIPath(mUri, VideoToServerActivity.this);
                Log.d(TAG, "Recorded Video Path " + mPathToStoredVideo);

                /// Store the video to your server
                uploadVideoToServer(mPathToStoredVideo);

            }
        }
    }

    @Override
    public void onPermissionsDenied(int requestCode, List<String> perms) {
        Log.d(TAG, "User has denied requested permission");
    }

    private void uploadVideoToServer(String pathToVideoFile) {
        File videoFile = new File(pathToVideoFile);
        RequestBody videoBody = RequestBody.create(MediaType.parse("video/*"), videoFile);
        MultipartBody.Part vFile = MultipartBody.Part.createFormData("video", videoFile.getName(),
            videoBody);

        Retrofit retrofit = new Retrofit.Builder()
                .baseUrl(SERVER_PATH)
                .addConverterFactory(GsonConverterFactory.create())
                .build();
        VideoInterface vInterface = retrofit.create(VideoInterface.class);
        Call<ResultObject> serverCom = vInterface.uploadVideoToServer(vFile);
        serverCom.enqueue(new Callback<ResultObject>() {
            @Override
            public void onResponse(Call<ResultObject> call, Response<ResultObject> response) {
                ResultObject result = response.body();
                if (!TextUtils.isEmpty(result.getSuccess())) {
                    Toast.makeText(getApplicationContext(), "Result " + result.getSuccess(),
                        Toast.LENGTH_LONG).show();
                    Log.d(TAG, "Result " + result.getSuccess());
                }
            }

            @Override
            public void onFailure(Call<ResultObject> call, Throwable t) {
                Log.d(TAG, "Error message " + t.getMessage());
            }
        });
    }

    private String getRealPathFromURIPath(Uri contentURI, Activity activity) {
        Cursor cursor = activity.getContentResolver().query(contentURI, null, null, null, null);
        if (cursor == null) {
            return contentURI.getPath();
        } else {
            cursor.moveToFirst();
            int idx = cursor.getColumnIndex(MediaStore.Images.ImageColumns.DATA);
            return cursor.getString(idx);
        }
    }

    /** Dealing with MediaCodec *******************************************************************/

    private MediaCodec mDecoder;
    private boolean mConfigured;
    private long mTimeoutUs = 10000l;

    /**! Encoder configuring
     * @param[in] surface
     * @param[in] width
     * @param[in] height
     * @param[in] csd0 */
    private synchronized void configure(Surface surface, int width, int height, ByteBuffer csd0) {
        if (mConfigured) { // просто флаг, чтобы знать, что декодер готов
            throw new IllegalStateException();
        }
        // создаем видео формат
        MediaFormat format = MediaFormat.createVideoFormat("video/avc", width, height);
        // передаем наш csd-0
        format.setByteBuffer("csd-0", csd0);

        // создаем декодер
        try {
            mDecoder = MediaCodec.createDecoderByType("video/avc");
        } catch (IOException e) {
            e.printStackTrace();
        }

        // конфигурируем декодер
        mDecoder.configure(format, surface, null, 0);
        mDecoder.start();
        mConfigured = true;
    }

    /**! Decoding dummy sample
     * @param[in] data
     * @param[in] offset
     * @param[in] size
     * @param[in] presentationTimeUs
     * @param[in] flags */
    void decodeSample(byte[] data, int offset, int size, long presentationTimeUs, int flags) {
        if (mConfigured) {
            // вызов блокирующий

            int index = mDecoder.dequeueInputBuffer(mTimeoutUs);
            if (index >= 0) {
                ByteBuffer buffer = mDecoder.getInputBuffers()[index];
                buffer.clear(); // обязательно сбросить позицию и размер буфера
                buffer.put(data, offset, size);
                // сообщаем системе о доступности буфера данных
                mDecoder.queueInputBuffer(index, 0, size, presentationTimeUs, flags);
            }
        }
    }
}
