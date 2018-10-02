package rhp.rushhourproject;

import android.content.Intent;
import android.os.Bundle;
import android.support.v7.app.AppCompatActivity;
import android.view.View;
import android.widget.Button;
import android.widget.TextView;


public class SolvePage extends AppCompatActivity {

    int steprn = 1;
    int page = 0;
    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.solvepage);
        Intent intent = getIntent();

        final String StringToIntent = intent.getStringExtra("StringToIntent");

        int length = StringToIntent.length();
        final int steps = length / 36;

        final TextView PageCount = findViewById(R.id.PageCount);
        String PageCountOutput = steprn + "/" + steps;
        PageCount.setText(PageCountOutput);

        Button PrevButton = findViewById(R.id.PrevBtn);
        Button NextButton = findViewById(R.id.NextBtn);

        final TextView textView1 = findViewById(R.id.textView1);
        final TextView textView2 = findViewById(R.id.textView2);
        final TextView textView3 = findViewById(R.id.textView3);
        final TextView textView4 = findViewById(R.id.textView4);
        final TextView textView5 = findViewById(R.id.textView5);
        final TextView textView6 = findViewById(R.id.textView6);
        final TextView textView7 = findViewById(R.id.textView7);
        final TextView textView8 = findViewById(R.id.textView8);
        final TextView textView9 = findViewById(R.id.textView9);
        final TextView textView10 = findViewById(R.id.textView10);
        final TextView textView11 = findViewById(R.id.textView11);
        final TextView textView12 = findViewById(R.id.textView12);
        final TextView textView13 = findViewById(R.id.textView13);
        final TextView textView14 = findViewById(R.id.textView14);
        final TextView textView15 = findViewById(R.id.textView15);
        final TextView textView16 = findViewById(R.id.textView16);
        final TextView textView17 = findViewById(R.id.textView17);
        final TextView textView18 = findViewById(R.id.textView18);
        final TextView textView19 = findViewById(R.id.textView19);
        final TextView textView20 = findViewById(R.id.textView20);
        final TextView textView21 = findViewById(R.id.textView21);
        final TextView textView22 = findViewById(R.id.textView22);
        final TextView textView23 = findViewById(R.id.textView23);
        final TextView textView24 = findViewById(R.id.textView24);
        final TextView textView25 = findViewById(R.id.textView25);
        final TextView textView26 = findViewById(R.id.textView26);
        final TextView textView27 = findViewById(R.id.textView27);
        final TextView textView28 = findViewById(R.id.textView28);
        final TextView textView29 = findViewById(R.id.textView29);
        final TextView textView30 = findViewById(R.id.textView30);
        final TextView textView31 = findViewById(R.id.textView31);
        final TextView textView32 = findViewById(R.id.textView32);
        final TextView textView33 = findViewById(R.id.textView33);
        final TextView textView34 = findViewById(R.id.textView34);
        final TextView textView35 = findViewById(R.id.textView35);
        final TextView textView36 = findViewById(R.id.textView36);

        String currchar = ""+StringToIntent.charAt(0);
        textView1.setText(currchar);
        currchar = ""+StringToIntent.charAt(1);
        textView2.setText(currchar);
        currchar = ""+StringToIntent.charAt(2);
        textView3.setText(currchar);
        currchar = ""+StringToIntent.charAt(3);
        textView4.setText(currchar);
        currchar = ""+StringToIntent.charAt(4);
        textView5.setText(currchar);
        currchar = ""+StringToIntent.charAt(5);
        textView6.setText(currchar);
        currchar = ""+StringToIntent.charAt(6);
        textView7.setText(currchar);
        currchar = ""+StringToIntent.charAt(7);
        textView8.setText(currchar);
        currchar = ""+StringToIntent.charAt(8);
        textView9.setText(currchar);
        currchar = ""+StringToIntent.charAt(9);
        textView10.setText(currchar);
        currchar = ""+StringToIntent.charAt(10);
        textView11.setText(currchar);
        currchar = ""+StringToIntent.charAt(11);
        textView12.setText(currchar);
        currchar = ""+StringToIntent.charAt(12);
        textView13.setText(currchar);
        currchar = ""+StringToIntent.charAt(13);
        textView14.setText(currchar);
        currchar = ""+StringToIntent.charAt(14);
        textView15.setText(currchar);
        currchar = ""+StringToIntent.charAt(15);
        textView16.setText(currchar);
        currchar = ""+StringToIntent.charAt(16);
        textView17.setText(currchar);
        currchar = ""+StringToIntent.charAt(17);
        textView18.setText(currchar);
        currchar = ""+StringToIntent.charAt(18);
        textView19.setText(currchar);
        currchar = ""+StringToIntent.charAt(19);
        textView20.setText(currchar);
        currchar = ""+StringToIntent.charAt(20);
        textView21.setText(currchar);
        currchar = ""+StringToIntent.charAt(21);
        textView22.setText(currchar);
        currchar = ""+StringToIntent.charAt(22);
        textView23.setText(currchar);
        currchar = ""+StringToIntent.charAt(23);
        textView24.setText(currchar);
        currchar = ""+StringToIntent.charAt(24);
        textView25.setText(currchar);
        currchar = ""+StringToIntent.charAt(25);
        textView26.setText(currchar);
        currchar = ""+StringToIntent.charAt(26);
        textView27.setText(currchar);
        currchar = ""+StringToIntent.charAt(27);
        textView28.setText(currchar);
        currchar = ""+StringToIntent.charAt(28);
        textView29.setText(currchar);
        currchar = ""+StringToIntent.charAt(29);
        textView30.setText(currchar);
        currchar = ""+StringToIntent.charAt(30);
        textView31.setText(currchar);
        currchar = ""+StringToIntent.charAt(31);
        textView32.setText(currchar);
        currchar = ""+StringToIntent.charAt(32);
        textView33.setText(currchar);
        currchar = ""+StringToIntent.charAt(33);
        textView34.setText(currchar);
        currchar = ""+StringToIntent.charAt(34);
        textView35.setText(currchar);
        currchar = ""+StringToIntent.charAt(35);
        textView36.setText(currchar);

        NextButton.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                if((steprn+1) <= steps)
                {
                    steprn++;
                    String PageCountOutput2 = steprn + "/" + steps;
                    PageCount.setText(PageCountOutput2);
                    page++;
                    String poschar = ""+StringToIntent.charAt(page * 36);
                    textView1.setText(poschar);
                    poschar = ""+StringToIntent.charAt(1 + (page * 36));
                    textView2.setText(poschar);
                    poschar = ""+StringToIntent.charAt(2 + (page * 36));
                    textView3.setText(poschar);
                    poschar = ""+StringToIntent.charAt(3 + (page * 36));
                    textView4.setText(poschar);
                    poschar = ""+StringToIntent.charAt(4 + (page * 36));
                    textView5.setText(poschar);
                    poschar = ""+StringToIntent.charAt(5 + (page * 36));
                    textView6.setText(poschar);
                    poschar = ""+StringToIntent.charAt(6 + (page * 36));
                    textView7.setText(poschar);
                    poschar = ""+StringToIntent.charAt(7 + (page * 36));
                    textView8.setText(poschar);
                    poschar = ""+StringToIntent.charAt(8 + (page * 36));
                    textView9.setText(poschar);
                    poschar = ""+StringToIntent.charAt(9 + (page * 36));
                    textView10.setText(poschar);
                    poschar = ""+StringToIntent.charAt(10 + (page * 36));
                    textView11.setText(poschar);
                    poschar = ""+StringToIntent.charAt(11 + (page * 36));
                    textView12.setText(poschar);
                    poschar = ""+StringToIntent.charAt(12 + (page * 36));
                    textView13.setText(poschar);
                    poschar = ""+StringToIntent.charAt(13 + (page * 36));
                    textView14.setText(poschar);
                    poschar = ""+StringToIntent.charAt(14 + (page * 36));
                    textView15.setText(poschar);
                    poschar = ""+StringToIntent.charAt(15 + (page * 36));
                    textView16.setText(poschar);
                    poschar = ""+StringToIntent.charAt(16 + (page * 36));
                    textView17.setText(poschar);
                    poschar = ""+StringToIntent.charAt(17 + (page * 36));
                    textView18.setText(poschar);
                    poschar = ""+StringToIntent.charAt(18 + (page * 36));
                    textView19.setText(poschar);
                    poschar = ""+StringToIntent.charAt(19 + (page * 36));
                    textView20.setText(poschar);
                    poschar = ""+StringToIntent.charAt(20 + (page * 36));
                    textView21.setText(poschar);
                    poschar = ""+StringToIntent.charAt(21 + (page * 36));
                    textView22.setText(poschar);
                    poschar = ""+StringToIntent.charAt(22 + (page * 36));
                    textView23.setText(poschar);
                    poschar = ""+StringToIntent.charAt(23 + (page * 36));
                    textView24.setText(poschar);
                    poschar = ""+StringToIntent.charAt(24 + (page * 36));
                    textView25.setText(poschar);
                    poschar = ""+StringToIntent.charAt(25 + (page * 36));
                    textView26.setText(poschar);
                    poschar = ""+StringToIntent.charAt(26 + (page * 36));
                    textView27.setText(poschar);
                    poschar = ""+StringToIntent.charAt(27 + (page * 36));
                    textView28.setText(poschar);
                    poschar = ""+StringToIntent.charAt(28 + (page * 36));
                    textView29.setText(poschar);
                    poschar = ""+StringToIntent.charAt(29 + (page * 36));
                    textView30.setText(poschar);
                    poschar = ""+StringToIntent.charAt(30 + (page * 36));
                    textView31.setText(poschar);
                    poschar = ""+StringToIntent.charAt(31 + (page * 36));
                    textView32.setText(poschar);
                    poschar = ""+StringToIntent.charAt(32 + (page * 36));
                    textView33.setText(poschar);
                    poschar = ""+StringToIntent.charAt(33 + (page * 36));
                    textView34.setText(poschar);
                    poschar = ""+StringToIntent.charAt(34 + (page * 36));
                    textView35.setText(poschar);
                    poschar = ""+StringToIntent.charAt(35 + (page * 36));
                    textView36.setText(poschar);
                }
            }
        });

        PrevButton.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                if((steprn-1) >= 1)
                {
                    steprn--;
                    String PageCountOutput2 = steprn + "/" + steps;
                    PageCount.setText(PageCountOutput2);
                    page--;
                    String poschar = ""+StringToIntent.charAt(page * 36);
                    textView1.setText(poschar);
                    poschar = ""+StringToIntent.charAt(1 + (page * 36));
                    textView2.setText(poschar);
                    poschar = ""+StringToIntent.charAt(2 + (page * 36));
                    textView3.setText(poschar);
                    poschar = ""+StringToIntent.charAt(3 + (page * 36));
                    textView4.setText(poschar);
                    poschar = ""+StringToIntent.charAt(4 + (page * 36));
                    textView5.setText(poschar);
                    poschar = ""+StringToIntent.charAt(5 + (page * 36));
                    textView6.setText(poschar);
                    poschar = ""+StringToIntent.charAt(6 + (page * 36));
                    textView7.setText(poschar);
                    poschar = ""+StringToIntent.charAt(7 + (page * 36));
                    textView8.setText(poschar);
                    poschar = ""+StringToIntent.charAt(8 + (page * 36));
                    textView9.setText(poschar);
                    poschar = ""+StringToIntent.charAt(9 + (page * 36));
                    textView10.setText(poschar);
                    poschar = ""+StringToIntent.charAt(10 + (page * 36));
                    textView11.setText(poschar);
                    poschar = ""+StringToIntent.charAt(11 + (page * 36));
                    textView12.setText(poschar);
                    poschar = ""+StringToIntent.charAt(12 + (page * 36));
                    textView13.setText(poschar);
                    poschar = ""+StringToIntent.charAt(13 + (page * 36));
                    textView14.setText(poschar);
                    poschar = ""+StringToIntent.charAt(14 + (page * 36));
                    textView15.setText(poschar);
                    poschar = ""+StringToIntent.charAt(15 + (page * 36));
                    textView16.setText(poschar);
                    poschar = ""+StringToIntent.charAt(16 + (page * 36));
                    textView17.setText(poschar);
                    poschar = ""+StringToIntent.charAt(17 + (page * 36));
                    textView18.setText(poschar);
                    poschar = ""+StringToIntent.charAt(18 + (page * 36));
                    textView19.setText(poschar);
                    poschar = ""+StringToIntent.charAt(19 + (page * 36));
                    textView20.setText(poschar);
                    poschar = ""+StringToIntent.charAt(20 + (page * 36));
                    textView21.setText(poschar);
                    poschar = ""+StringToIntent.charAt(21 + (page * 36));
                    textView22.setText(poschar);
                    poschar = ""+StringToIntent.charAt(22 + (page * 36));
                    textView23.setText(poschar);
                    poschar = ""+StringToIntent.charAt(23 + (page * 36));
                    textView24.setText(poschar);
                    poschar = ""+StringToIntent.charAt(24 + (page * 36));
                    textView25.setText(poschar);
                    poschar = ""+StringToIntent.charAt(25 + (page * 36));
                    textView26.setText(poschar);
                    poschar = ""+StringToIntent.charAt(26 + (page * 36));
                    textView27.setText(poschar);
                    poschar = ""+StringToIntent.charAt(27 + (page * 36));
                    textView28.setText(poschar);
                    poschar = ""+StringToIntent.charAt(28 + (page * 36));
                    textView29.setText(poschar);
                    poschar = ""+StringToIntent.charAt(29 + (page * 36));
                    textView30.setText(poschar);
                    poschar = ""+StringToIntent.charAt(30 + (page * 36));
                    textView31.setText(poschar);
                    poschar = ""+StringToIntent.charAt(31 + (page * 36));
                    textView32.setText(poschar);
                    poschar = ""+StringToIntent.charAt(32 + (page * 36));
                    textView33.setText(poschar);
                    poschar = ""+StringToIntent.charAt(33 + (page * 36));
                    textView34.setText(poschar);
                    poschar = ""+StringToIntent.charAt(34 + (page * 36));
                    textView35.setText(poschar);
                    poschar = ""+StringToIntent.charAt(35 + (page * 36));
                    textView36.setText(poschar);
                }
            }
        });
    }
}
