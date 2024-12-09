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
        }
    }
};

main()
{
    cGUI theGUI;
    return 0;
}
