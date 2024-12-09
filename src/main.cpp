#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <vector>
#include <algorithm>
#include <wex.h>
#include "cStarterGUI.h"

class cGUI : public cStarterGUI
{
public:
    cGUI()
        : cStarterGUI(
              "Starter",
              {50, 50, 1000, 500}),
          fdrawing(false)
    {

        fm.events().mouseMove(
            [&](wex::sMouse &ms)
            {
                if (!ms.left)
                {
                    if (!fdrawing)
                        return;
                    fdrawing = false;
                    box();
                }
                else
                {
                    fdrawing = true;
                    myTrace.push_back(cxy(ms.x, ms.y));
                }
                fm.update();
            });

        show();
        run();
    }

private:
    bool fdrawing;
    std::vector<cxy> myTrace;
    cxy topleft;
    cxy wh;

    void draw(wex::shapes &S)
    {
        S.fill();
        S.color(0x00FF00);
        for (int k = 0; k < myTrace.size(); k++)
            S.circle(myTrace[k].x, myTrace[k].y, 10);
        if (!fdrawing)
        {
            S.color(0x0000FF);
            for (int k = 1; k < myTrace.size(); k++)
                S.line(myTrace[k - 1], myTrace[k]);
            S.fill(false);
            S.color(0xFF0000);
            S.rectangle({(int)topleft.x,(int)topleft.y,(int)wh.x,(int)wh.y});
        }
    }

    void box()
    {

        topleft = myTrace[0];
        for (auto &p : myTrace)
        {
            if (p.x < topleft.x)
                topleft.x = p.x;
            if (p.y < topleft.y)
                topleft.y = p.y;
        }

        wh = cxy(0,0);
        for (auto &p : myTrace)
        {
            if (p.x - topleft.x > wh.x)
                wh.x = p.x - topleft.x;
            if (p.y - topleft.y > wh.y)
                wh.y = p.y - topleft.y;
        }
        // std::vector<double> ret;
        // double xscale = 400 / wh.x;
        // double yscale = 400 / wh.y;
        // if (yscale < xscale)
        //     ret.push_back(yscale);
        // else
        //     ret.push_back(xscale);
        // ret.push_back(topleft.x);
        // ret.push_back(topleft.y);


    }
};

main()
{
    cGUI theGUI;
    return 0;
}
