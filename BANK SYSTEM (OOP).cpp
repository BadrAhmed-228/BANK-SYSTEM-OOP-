#include <iostream>
#include "clsBankClient.h"
#include "clsInputValidate.h"
#include "clsUtil.h"
#include <iomanip>
#include "clsMainScreen.h"
#include "clsLoginScreen.h"

using namespace std;

int main()
{

    while (true)
    {
        if (!clsLoginScreen::Login())
        {
            break;
        }
    }

    return 0;
}
