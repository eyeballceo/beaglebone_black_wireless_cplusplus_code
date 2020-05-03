#include <iostream>
#include <fstream>
#include <string>
using namespace std;

void removeTrigger(int lightNumber)
{
    std::fstream fs;
    std::string lightNumberString = std::to_string(lightNumber);
    fs.open("/sys/class/leds/beaglebone:green:usr" + lightNumberString + "/trigger", std::fstream::out);
    fs << "none";
    fs.close();
}

void manipulateLights(int lightNumber, int commandNumber)
{
    std::fstream fs;
    std::string lightNumberString = std::to_string(lightNumber);
    if (commandNumber == 1)
    {
        fs.open("/sys/class/leds/beaglebone:green:usr" + lightNumberString + "/brightness", std::fstream::out);
        fs << "1";
        fs.close();
    }
    else if (commandNumber == 2)
    {
        fs.open("/sys/class/leds/beaglebone:green:usr" + lightNumberString + "/brightness", std::fstream::out);
        fs << "0";
        fs.close();
    }
    else if (commandNumber == 3)
    {
        fs.open("/sys/class/leds/beaglebone:green:usr" + lightNumberString + "/trigger", std::fstream::out);
        fs << "timer";
        fs.close();
        fs.open("/sys/class/leds/beaglebone:green:usr" + lightNumberString + "/delay_on", std::fstream::out);
        fs << "50";
        fs.close();
        fs.open("/sys/class/leds/beaglebone:green:usr" + lightNumberString + "/delay_off", std::fstream::out);
        fs << "50";
        fs.close();
    }
    else if (commandNumber == 4)
    {
        fs.open("/sys/class/leds/beaglebone:green:usr" + lightNumberString + "/trigger", std::fstream::in);
        string line;
        while (getline(fs, line))
            cout << line << endl;
        fs.close();
    }
    else
    {
        cout << "Invalid command" << endl;
    }
    cout << "Finished the LED flash program" << endl;
}

void lightingOptions(int lightNumber)
{
    int commandNumber;
    cout << "Enter the number for your lighting command (1: ON, 2: OFF, 3: FLASH or 4: STATUS)." << endl;
    cin >> commandNumber;
    while (commandNumber > 4 || commandNumber < 1)
    {
        cout << "Please enter a valid command (1: ON, 2: OFF, 3: FLASH or 4: STATUS)." << endl;
        cin >> commandNumber;
    }
    removeTrigger(lightNumber);
    manipulateLights(lightNumber, commandNumber);
}

void getLightNumber()
{
    int lightNumber;
    cout << "Starting Sam's LED function." << endl;
    cout << "Enter the number (0-3) LED you want to use." << endl;
    cin >> lightNumber;
    while (lightNumber > 3 || lightNumber < 0)
    {
        cout << "Please enter a value between 0 and 3." << endl;
        cin >> lightNumber;
    }
    lightingOptions(lightNumber);
}

int main()
{
    cout << "Starting Sam's LED function." << endl;
    getLightNumber();
}