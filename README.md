<!-- Proje-Resmi -->

## 👀 esp32_home-assistant_telegram-bot Overview  
<h1 align="center">Home Assistant controlled by telegram bot</h1>  


## 🚀 Features  
<h1 align="center">The design aims to provide real-time control and monitoring by leveraging a Telegram bot to verify collected data. This core functionality is extended to enable immediate awareness through voice notifications delivered directly via both the user's mobile device and the home system.</h1>  


## 🔎 Preparation
1. `Find your wifi's name and password`
<details>
<summary>2. Open the Telegram for the Bot Token and follow these steps:</summary>

1. Open Telegram and search for `@BotFather`.
2. Start a chat with BotFather by typing `/start`.
3. Create a new bot with the `/newbot` command.
4. Follow the prompts to name your bot and choose a username.
5. Copy the API token provided by BotFather.

</details>
<details>
<summary>3. Get your Telegram Chat ID:</summary>

1. Open Telegram and search for `@userinfobot` or `@get_id_bot`.
2. Start a chat with the bot by typing `/start`.
3. The bot will reply with your **numeric user ID**.
4. For group chat ID:
    1. Add your bot to the group.
    2. Send a message in the group mentioning the bot.
    3. Use the API call:
       ```
       https://api.telegram.org/bot<YOUR_BOT_TOKEN>/getUpdates
       ```
       - Look for `"chat":{"id": ...}` in the JSON response.
       - The `chat.id` is your group chat ID (usually negative for groups, e.g., `-1001234567890`).

</details>


## 📦 Setup 
1. `Refer to the circuit diagram`
2. `Install the 'Arduino IDE' software and open 'esp32_home-assistan_telegram.ino' file`
3. `Paste your wifi, bot token and chat id inf.`
4. `File>Preferences>Additional Boards Manager URLs:(Click the double window button)`
>Paste this code  
```bash
https://dl.espressif.com/dl/package_esp32_index.json
```
5. `Click 'OK'`  
6. `Tools>Board>Boards Manager...`  
7. `Search 'esp32' by Espressif Systems, and install it` 
> ⚠️ **Warning:** Make sure you have installed the correct USB driver (CH340, CH341, FT232R / FTDI Driver, CP2102) before connecting the ESP32CAM to your computer.
8. `Plug the ESP32CAM into your computer`
9. `Tools>Port>'Select the esp's port'`
10. `Tools>Manage Libraries...>Install the libraries used in the code`
11. `Click the 'upload ➡️' button`  
✅ **To make sure it has been uploaded successfully, you should see the message 'Done uploading'**  


## 🎉 Run  
1. `Disconnect the IO0-GND connection(disable programming mode)`  
2. `Press the reset button on the esp32cam`
3. `You can use /start command in your telegram bot`


## 🔒 License  
<h1 align="center">📜 GPL-3.0 License</h1>  
