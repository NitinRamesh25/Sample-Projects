package com.panda.compass;

import androidx.appcompat.app.AppCompatActivity;
import androidx.arch.core.util.Function;
import androidx.core.app.ActivityCompat;
import androidx.core.content.ContextCompat;

import android.Manifest;
import android.content.pm.PackageManager;
import android.hardware.Sensor;
import android.hardware.SensorEvent;
import android.hardware.SensorEventListener;
import android.hardware.SensorManager;
import android.os.Bundle;
import android.widget.ImageView;
import android.widget.Toast;

public class MainActivity extends AppCompatActivity implements SensorEventListener {

    private ImageView mCompassImage = null;

    private SensorManager mSensorManager = null;
    private Sensor mAccelerometerSensor = null;
    private Sensor mMagneticSensor = null;
    private final int PERMISSION_CODE = 10;

    private float[] rMat = new float[9];
    private float[] orientation = new float[9];
    private float[] mAccelerometerData = new float[3];
    private float[] mMagnetometerData = new float[3];
    private int mAzimuth = 0;

    private boolean mGotAccelerometerData = false;
    private boolean mGotMagnetometerData = false;

    @Override
    public void onSensorChanged(SensorEvent event) {
        int sensorType = event.sensor.getType();
        switch (sensorType) {
            case Sensor.TYPE_ACCELEROMETER:
                System.arraycopy(event.values, 0, mAccelerometerData, 0, event.values.length);
                mGotAccelerometerData = true;
                break;

            case Sensor.TYPE_MAGNETIC_FIELD:
                System.arraycopy(event.values, 0, mMagnetometerData, 0, event.values.length);
                mGotMagnetometerData = true;
                break;

            default:
                Toast.makeText(this, "Unknown sensor invoked", Toast.LENGTH_SHORT).show();
                break;
        }

        if (mGotAccelerometerData && mGotMagnetometerData) {
            SensorManager.getRotationMatrix(rMat, null, mAccelerometerData, mMagnetometerData);
            mAzimuth = (int) Math.toDegrees(SensorManager.getOrientation(rMat, orientation)[0]);
            mAzimuth = Math.round(mAzimuth);
            mAzimuth = mAzimuth - (mAzimuth % 5);
        }

        mCompassImage.setRotation(-mAzimuth);
    }

    @Override
    public void onAccuracyChanged(Sensor sensor, int accuracy) {
    }

    @Override
    protected void onResume() {
        super.onResume();
        mSensorManager.registerListener(this, mAccelerometerSensor, SensorManager.SENSOR_DELAY_FASTEST);
        mSensorManager.registerListener(this, mMagneticSensor, SensorManager.SENSOR_DELAY_FASTEST);
    }

    @Override
    protected void onPause() {
        super.onPause();
        mSensorManager.unregisterListener(this);
    }

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        setupPermissions();
        initWidgets();
        initSensors();
    }

    private void setupPermissions() {
        int permissionStatus = ContextCompat.checkSelfPermission(this,
                Manifest.permission.ACTIVITY_RECOGNITION);

        if (permissionStatus != PackageManager.PERMISSION_GRANTED) {
            ActivityCompat.requestPermissions(this,
                    new String[]{Manifest.permission.ACTIVITY_RECOGNITION}, PERMISSION_CODE);
        }
    }

    private void initWidgets() {
        mCompassImage = findViewById(R.id.compass);
    }

    private void initSensors() {
        mSensorManager = (SensorManager) getSystemService(SENSOR_SERVICE);
        mMagneticSensor = mSensorManager.getDefaultSensor(Sensor.TYPE_MAGNETIC_FIELD);
        mAccelerometerSensor = mSensorManager.getDefaultSensor(Sensor.TYPE_ACCELEROMETER);

        if ((mMagneticSensor == null) || (mAccelerometerSensor == null))
            Toast.makeText(this, "could not find sensor", Toast.LENGTH_SHORT).show();
    }
}
