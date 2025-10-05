class StarterKitItem
{
    string classname;
    int quantity;
}

class StarterKitConfig
{
    ref array<ref StarterKitItem> items;
}

void GiveJsonStarterKit(PlayerBase player)
{
    if (!player) return;

    string path = "$profile:\\StarterKit.json";
    if (!FileExist(path))
    {
        Print("[StarterKit] ERROR: StarterKit.json not found in $profile!");
        return;
    }

    StarterKitConfig config;
    JsonFileLoader<StarterKitConfig>.JsonLoadFile(path, config);

    if (!config || !config.items)
    {
        Print("[StarterKit] ERROR: Invalid JSON format!");
        return;
    }

    foreach (StarterKitItem item : config.items)
    {
        for (int i = 0; i < item.quantity; i++)
        {
            player.GetInventory().CreateInInventory(item.classname);
        }
    }

    player.MessageStatus("[Server] Starter kit received!");
}
