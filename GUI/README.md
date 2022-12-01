## Installation

This is the **Qt6/5** version of **starfetch**. Look at the bottom if you want to use the program on **Linux/\*BSD/Apple**. If on **Windows** you'll need to download and install Qt - [Qt installer](https://www.qt.io/cs/c/?cta_guid=074ddad0-fdef-4e53-8aa8-5e8a876d6ab4&signature=AAH58kEJJxpduKtfibJ40aRNSB4V5QaI1A&pageId=12602948080&placement_guid=99d9dd4f-5681-48d2-b096-470725510d34&click=559deaff-10e4-44a7-a78c-ef8b98f3c31a&hsutk=&canon=https%3A%2F%2Fwww.qt.io%2Fdownload-open-source&portal_id=149513&redirect_url=APefjpGq5H2gLEy0rkYfu04Stc7zjmm0KqS_XaAVoOUeI1pUOzGQZgD_zg87kf-KWNMA8LagnlFie8sOAzzTMW8z48C4QlIP08Ykoqpk2QaLznoki0aaOBah-YfMzg2wugOl_TcZQF2S) and install Qt **manually** from the GUI installer.

After that import all project files in **Qt Creator** and compile with **CTRL + r**. From now on, you can use the compiled **starfetch** executable.

You need to install the CLI version of **starfetch** first, so all .json files to be copied to your system.

---

If on **Linux/\*BSD/Apple** compile with:

```bash
cmake .
make -j8 # 8 cores/threads to use in parallel compile
sudo make install
```
