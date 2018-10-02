package rhp.rushhourproject;

import android.content.Context;
import android.content.Intent;
import android.os.Bundle;
import android.support.v7.app.AppCompatActivity;
import android.util.Log;
import android.view.View;
import android.widget.Button;
import android.widget.EditText;
import android.widget.Toast;

import java.util.ArrayList;

public class MainActivity extends AppCompatActivity {

    // Used to load the 'native-lib' library on application startup.
    static {
        System.loadLibrary("rushhour");
    }

    //public native String stringFromJNI();
    public native String StringSolver(String hello);

    /*boolean timerrun = false;
    TextView Timer = findViewById(R.id.Timer);
    Handler customHandler = new Handler();
    Long startTime= 0L, timeInMiliseconds=0L,timeSwapBuff=0L,updateTime=0L;

    Runnable updateTimerThread = new Runnable() {
        @Override
        public void run() {
            timeInMiliseconds = SystemClock.uptimeMillis()-startTime;
            updateTime = timeSwapBuff+timeInMiliseconds;
            int secs = (int)(updateTime/1000);
            int min = secs/60;
            secs%=60;
            int miliseconds = (int)(updateTime%1000);
            Timer.setText(""+min+String.format("%02d",secs)+":"+String.format("%03d",miliseconds));
            customHandler.postDelayed(this,0);
        }
    };
    */
    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
       /* var viewGroup = findViewById<LinearLayout>(Resource.Id.MyLayout);

        for (int i = 0; i < viewGroup.ChildCount; i++)
        {
            var childView = viewGroup.GetChildAt(i);

            if (childView is TextView)
            {
                //do what ever you have to do
            }
        }*/
        final ArrayList<EditText> InputText = new ArrayList<EditText>();
        InputText.add((EditText)findViewById(R.id.editText1));
        InputText.add((EditText)findViewById(R.id.editText2));
        InputText.add((EditText)findViewById(R.id.editText3));
        InputText.add((EditText)findViewById(R.id.editText4));
        InputText.add((EditText)findViewById(R.id.editText5));
        InputText.add((EditText)findViewById(R.id.editText6));
        InputText.add((EditText)findViewById(R.id.editText7));
        InputText.add((EditText)findViewById(R.id.editText8));
        InputText.add((EditText)findViewById(R.id.editText9));
        InputText.add((EditText)findViewById(R.id.editText10));
        InputText.add((EditText)findViewById(R.id.editText11));
        InputText.add((EditText)findViewById(R.id.editText12));
        InputText.add((EditText)findViewById(R.id.editText13));
        InputText.add((EditText)findViewById(R.id.editText14));
        InputText.add((EditText)findViewById(R.id.editText15));
        InputText.add((EditText)findViewById(R.id.editText16));
        InputText.add((EditText)findViewById(R.id.editText17));
        InputText.add((EditText)findViewById(R.id.editText18));
        InputText.add((EditText)findViewById(R.id.editText19));
        InputText.add((EditText)findViewById(R.id.editText20));
        InputText.add((EditText)findViewById(R.id.editText21));
        InputText.add((EditText)findViewById(R.id.editText22));
        InputText.add((EditText)findViewById(R.id.editText23));
        InputText.add((EditText)findViewById(R.id.editText24));
        InputText.add((EditText)findViewById(R.id.editText25));
        InputText.add((EditText)findViewById(R.id.editText26));
        InputText.add((EditText)findViewById(R.id.editText27));
        InputText.add((EditText)findViewById(R.id.editText28));
        InputText.add((EditText)findViewById(R.id.editText29));
        InputText.add((EditText)findViewById(R.id.editText30));
        InputText.add((EditText)findViewById(R.id.editText31));
        InputText.add((EditText)findViewById(R.id.editText32));
        InputText.add((EditText)findViewById(R.id.editText33));
        InputText.add((EditText)findViewById(R.id.editText34));
        InputText.add((EditText)findViewById(R.id.editText35));
        InputText.add((EditText)findViewById(R.id.editText36));

        Button GoBtn = findViewById(R.id.button1);
        GoBtn.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                // Do whatever here
                //TextView OutputText = (TextView) findViewById(R.id.OutputText);
                char[][] board = new char[6][6];

                String Test = "";
                for(int i = 0; i < InputText.size(); i++)
                {
                    if(!InputText.get(i).getText().toString().matches("")) {
                        Test = Test + InputText.get(i).getText();
                    }else{
                        Test = Test + 'O';
                    }
                }
                Log.i("TAG", Test);

                for(int i = 0; i < InputText.size(); i++)
                {
                    if(InputText.get(i).getText().toString().matches("")) {
                        board[0][0] = 'O';
                    } else{
                        board[0][0] = InputText.get(i).getText().toString().charAt(0);
                    }
                }
                //OutputText.setText(board[0][0] + "");
                for(int i = 0; i < 6; i++)
                {
                    for(int j = 0; j < 6; j++)
                    {
                        Log.d("Array",board[i][j] + "");
                    }
                }

                String StringToC;
                StringBuilder StringBuild = new StringBuilder();
                for(int i = 0; i < 6; i++) {
                    for (int j = 0; j < 6; j++) {
                        StringBuild.append(board[i][j]);
                    }
                }
                StringToC = StringBuild.toString();
                String StringFromC = "OOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOO";
                Log.d("I","String wird übergeben!");
                try {
                    StringFromC = StringSolver(Test);
                    Log.i("TAG", StringFromC);
                }catch (Exception e){
                    Context context = getApplicationContext();
                    CharSequence text = "Could not solve!";
                    int duration = Toast.LENGTH_SHORT;
                    Toast toast = Toast.makeText(context, text, duration);
                    toast.show();
                }

                if(StringFromC != null && StringFromC.length() > 35)
                {
                try{
                    Intent myIntent = new Intent(MainActivity.this, SolvePage.class);
                    Log.d("Das ist er:", "" + StringFromC);
                    myIntent.putExtra("StringToIntent", StringFromC);
                    MainActivity.this.startActivity(myIntent);
                }catch (Exception e){
                    Context context = getApplicationContext();
                    CharSequence text = "Could not solve!";
                    int duration = Toast.LENGTH_SHORT;
                    Toast toast = Toast.makeText(context, text, duration);
                    toast.show();
                }

                }else
                {
                    Context context = getApplicationContext();
                    CharSequence text = "Please use a valid field";
                    int duration = Toast.LENGTH_SHORT;
                    Toast toast = Toast.makeText(context, text, duration);
                    toast.show();
                }
            }
        });
        Button ResetBtn = findViewById(R.id.button2);
        ResetBtn.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                /*if(!timerrun)
                {
                    startTime = SystemClock.uptimeMillis();
                    customHandler.postDelayed(updateTimerThread,0);
                }else
                {
                    timerrun = true;
                    timeSwapBuff+=timeInMiliseconds;
                    customHandler.removeCallbacks(updateTimerThread);
                }*/
                for(int i = 0; i < InputText.size(); i++)
                {
                    if(i != 13 && i != 14)
                    {
                        EditText InputTextField = InputText.get(i);
                        InputTextField.setText("");
                    }else{
                        EditText InputTextField = InputText.get(i);
                        InputTextField.setText("R");
                    }
                }
            }
        });
    }

}
