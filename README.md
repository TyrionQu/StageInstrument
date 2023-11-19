How to update the app?
---------------
The repo for the update app is
https://github.com/DaisyKid/wingup/tree/stage

The repo for the http server is
https://github.com/DaisyKid/Crow/tree/stage


0. Update app is ./updater/GUP.exe and update info is ./updater/gup.xml
1. GUP.exe sends HTTP/1.1 GET /params?version=1.0(for example) to http://49.235.100.232:8080/
2. A http service is deployed in 49.235.100.232:8080. It will compare the version in request
with the local version. If the local version is higher, it will update the xml info. And GUP.exe
will download the setup file if the response from server is updated.

TODO:
0. setup file is not verified now so will be deleted by the system after download.
1. update app should block the main app
