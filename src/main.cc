#include <memory>
#include "command/factory/factory.h"

using namespace std;

int main(int argc, char *argv[])
{
    ParameterValidator validator(argc, argv);
    string base_url = validator.GetBaseUrl();

    Cache cache;
    cache.SetBaseUrl(base_url);

    unique_ptr<Invoker> invoker = make_unique<Invoker>(cache);

    Factory factory;
    factory.MakeCommands(invoker, cache);

    AnsiColor color;
    color.Title("======================================");
    color.Title("========== FIFO Chat Client ==========");
    color.Title("======================================");
    invoker->PrintCommands();
    bool receive_commands = true;
    string userSelection;

    do
    {
        string baseUrl = validator.GetBaseUrl();
        color.Text("\n> Waiting for a command... : ");
        userSelection.clear();
        cin >> userSelection;

        if (cin.fail())
        {
            cin.clear();
            continue;
        }

        try
        {
            receive_commands = invoker->Invoke(userSelection);
        }
        catch (const InvalidCommandException &ex)
        {
            color.ErrorWithLineFeed(ex.what());
        }
        catch (const BaseException &ex)
        {
            color.ErrorWithLineFeed(ex.what());
        }

    } while (receive_commands);

    color.Title("======================================");
}
