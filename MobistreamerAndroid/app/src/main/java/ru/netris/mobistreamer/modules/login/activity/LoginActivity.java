package ru.netris.mobistreamer.modules.login.activity;

import android.animation.Animator;
import android.animation.AnimatorListenerAdapter;
import android.annotation.TargetApi;
import android.content.Intent;
import android.content.pm.PackageManager;
import android.os.Build;
import android.os.Bundle;
import android.support.annotation.NonNull;
import android.support.design.widget.Snackbar;
import android.support.v7.app.AppCompatActivity;
import android.util.Log;
import android.view.KeyEvent;
import android.view.View;
import android.view.View.OnClickListener;
import android.view.inputmethod.EditorInfo;
import android.widget.AutoCompleteTextView;
import android.widget.Button;
import android.widget.EditText;
import android.widget.TextView;

import ru.netris.mobistreamer.R;
import ru.netris.mobistreamer.modules.video.activity.Camera2Activity;
import ru.netris.mobistreamer.modules.login.network.PortalConnection;

import static android.Manifest.permission.CAMERA;
import static android.Manifest.permission.READ_CONTACTS;

//import ru.netris.posixsockets.TCPNativeClient;

//import ru.netris.nativesocket.java.NativeSocketClient;

/**
 * A login screen that offers login via email/password.
 */
public class LoginActivity extends AppCompatActivity {


    public static final String TAG = "LoginActivity";

    private static final int REQUEST_READ_CONTACTS = 0;
    private static final int REQUEST_CAMERA = 1;

    private AutoCompleteTextView mEmailView;
    private EditText mPasswordView;
    private View mProgressView;
    private View mLoginFormView;
    Button mEmailSignInButton;
    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_login);
        // Set up the login form.
        mEmailView = (AutoCompleteTextView) findViewById(R.id.email);
        populateAutoComplete();

        mPasswordView = (EditText) findViewById(R.id.password);
        mPasswordView.setOnEditorActionListener(new TextView.OnEditorActionListener() {
            @Override
            public boolean onEditorAction(TextView textView, int id, KeyEvent keyEvent) {
                if (id == R.id.login || id == EditorInfo.IME_NULL) {
                    return true;
                }
                return false;
            }
        });

        mEmailSignInButton = (Button) findViewById(R.id.email_sign_in_button);
        mEmailSignInButton.setOnClickListener(new OnClickListener() {
            @Override
            public void onClick(View view) {

                if(mEmailSignInButton.getText() == "Войти") {
                    setupLoadingState();
                    openActivity();
                }else{
                    cancelOpenActivity();
                }

//                attemptLogin();
            }
        });

        mLoginFormView = findViewById(R.id.form);
        mProgressView = findViewById(R.id.login_progress);


        setupInitState();
    }

    private boolean mayRequestVideo() {
        if (Build.VERSION.SDK_INT < Build.VERSION_CODES.M) {
            return true;
        }
        if (checkSelfPermission(CAMERA) == PackageManager.PERMISSION_GRANTED) {
            return true;
        }
        if (shouldShowRequestPermissionRationale(CAMERA)) {
            Log.d(TAG, "shouldShowRequestPermissionRationale(CAMERA)");
            Snackbar.make(findViewById(R.id.main), "Нужен доступ к камере",Snackbar.LENGTH_INDEFINITE).setAction(android.R.string.ok, new View.OnClickListener() {
                        @Override
                        @TargetApi(Build.VERSION_CODES.M)
                        public void onClick(View v) {
                            requestPermissions(new String[]{READ_CONTACTS}, REQUEST_READ_CONTACTS);
                        }
            });
//            Snackbar.make(mEmailView, R.string.permission_rationale, Snackbar.LENGTH_INDEFINITE)
//                    .setAction(android.R.string.ok, new View.OnClickListener() {
//                        @Override
//                        @TargetApi(Build.VERSION_CODES.M)
//                        public void onClick(View v) {
//                            requestPermissions(new String[]{READ_CONTACTS}, REQUEST_READ_CONTACTS);
//                        }
//                    });
        } else {
            requestPermissions(new String[]{CAMERA}, REQUEST_READ_CONTACTS);
        }
        return false;
    }

    void setupLoadingState() {
        // hide keyboard
        //
        runOnUiThread(new Runnable() {
            @Override
            public void run() {
                showProgress(true);
                mEmailSignInButton.setText("Отмена");
            }
        });
    }

    void setupInitState() {
        // focus to login
        //

        runOnUiThread(new Runnable() {
            @Override
            public void run() {
                showProgress(false);
                mEmailSignInButton.setText("Войти");
            }
        });
    }

    void cancelOpenActivity() {
        PortalConnection.getInstance().cancelAuth();
        setupInitState();
    }

    void openActivity() {

/*
        NativeSocketClient.HOST = IStreamConnection.STATIC_HOST;
        NativeSocketClient.PORT = IStreamConnection.STATIC_PORT;
        NativeSocketClient.getInstance().connect(new NativeSocketClient.CallbackConnection() {
            @Override
            public void connectedStream(boolean isConnect) {
                if(isConnect) {
                    IStreamConnection c = new IStreamConnection("",123, new IStreamConnection.Callback() {
                        @Override
                        public void onConnected() {

                        }

                        @Override
                        public void onDisconnected() {

                        }
                    });
                    c.registerCamera("");
                }
            }
        });
*/

//        aa_asinenko/38c6iJbui3

        PortalConnection.getInstance().auth("aa_asinenko","38c6iJbui3", this ,new PortalConnection.PortalConnectionCallback() {

            @Override
            public void onError(String message) {

                if(null != message) {
                    Log.d(TAG, message);
                }else{
                    Log.d(TAG, "ERROR AUTH");
                }
                setupInitState();
                // show message
            }

            @Override
            public void onSettings(final PortalConnection.ServerSettings settings) {
                Log.d(TAG, settings.ip);
                Log.d(TAG, settings.login);
                Log.d(TAG, settings.host);
                Log.d(TAG, settings.imei);
                Log.d(TAG, settings.live);
                Log.d(TAG, settings.stream);
                Log.d(TAG, settings.geohost);

                runOnUiThread(new Runnable() {
                    @Override
                    public void run() {
                        Intent intent = new Intent(getApplicationContext(), Camera2Activity.class);
                        intent.putExtra("Settings", settings);
                        startActivity(intent);
                        finish();
                    }
                });
            }

            @Override
            public void onStatus(int status) {

            }
        });
    }

    private void populateAutoComplete() {
        if (!mayRequestContacts()) {
            return;
        }
    }

    private boolean mayRequestContacts() {
        if (Build.VERSION.SDK_INT < Build.VERSION_CODES.M) {
            return true;
        }
        if (checkSelfPermission(READ_CONTACTS) == PackageManager.PERMISSION_GRANTED) {
            return true;
        }
        if (shouldShowRequestPermissionRationale(READ_CONTACTS)) {
            Snackbar.make(mEmailView, R.string.permission_rationale, Snackbar.LENGTH_INDEFINITE)
                    .setAction(android.R.string.ok, new View.OnClickListener() {
                        @Override
                        @TargetApi(Build.VERSION_CODES.M)
                        public void onClick(View v) {
                            requestPermissions(new String[]{READ_CONTACTS}, REQUEST_READ_CONTACTS);
                        }
                    });
        } else {
            requestPermissions(new String[]{READ_CONTACTS}, REQUEST_READ_CONTACTS);
        }
        return false;
    }

    @Override
    protected void onResume() {
        super.onResume();
        mayRequestVideo();
    }

    /**
     * Callback received when a permissions request has been completed.
     */
    @Override
    public void onRequestPermissionsResult(int requestCode, @NonNull String[] permissions,
                                           @NonNull int[] grantResults) {
        if (requestCode == REQUEST_READ_CONTACTS) {
            if (grantResults.length == 1 && grantResults[0] == PackageManager.PERMISSION_GRANTED) {
                populateAutoComplete();
            }
        }else if(requestCode == REQUEST_CAMERA) {
            if (grantResults.length == 1 && grantResults[0] == PackageManager.PERMISSION_GRANTED) {
                Log.d(TAG, "requestCode == REQUEST_CAMERA");
            }
        }
    }

    private boolean isEmailValid(String email) {
        //TODO: Replace this with your own logic
        return email.contains("@");
    }

    private boolean isPasswordValid(String password) {
        //TODO: Replace this with your own logic
        return password.length() > 4;
    }

    /**
     * Shows the progress UI and hides the login form.
     */
    @TargetApi(Build.VERSION_CODES.HONEYCOMB_MR2)
    private void showProgress(final boolean show) {
        // On Honeycomb MR2 we have the ViewPropertyAnimator APIs, which allow
        // for very easy animations. If available, use these APIs to fade-in
        // the progress spinner.
        if (Build.VERSION.SDK_INT >= Build.VERSION_CODES.HONEYCOMB_MR2) {
            int shortAnimTime = getResources().getInteger(android.R.integer.config_shortAnimTime);

            mLoginFormView.setVisibility(show ? View.GONE : View.VISIBLE);
            mLoginFormView.animate().setDuration(shortAnimTime).alpha(
                    show ? 0 : 1).setListener(new AnimatorListenerAdapter() {
                @Override
                public void onAnimationEnd(Animator animation) {
                    mLoginFormView.setVisibility(show ? View.GONE : View.VISIBLE);
                }
            });

//            mEmailView.setVisibility(show ? View.GONE : View.VISIBLE);
//            mPasswordView.setVisibility(show ? View.GONE : View.VISIBLE);


            mProgressView.setVisibility(show ? View.VISIBLE : View.GONE);
            mProgressView.animate().setDuration(shortAnimTime).alpha(
                    show ? 1 : 0).setListener(new AnimatorListenerAdapter() {
                @Override
                public void onAnimationEnd(Animator animation) {
                    mProgressView.setVisibility(show ? View.VISIBLE : View.GONE);
                }
            });
        } else {
            // The ViewPropertyAnimator APIs are not available, so simply show
            // and hide the relevant UI components.
            mProgressView.setVisibility(show ? View.VISIBLE : View.GONE);
//            mEmailView.setVisibility(show ? View.GONE : View.VISIBLE);
//            mPasswordView.setVisibility(show ? View.GONE : View.VISIBLE);
            mLoginFormView.setVisibility(show ? View.GONE : View.VISIBLE);
        }
    }
}

