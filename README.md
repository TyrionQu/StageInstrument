How to update the app?
---------------
The repo for the update app is
https://github.com/DaisyKid/wingup/tree/update

The repo for the http server is
https://github.com/DaisyKid/Crow/tree/stage


0. Update app is ./updater/GUP.exe and update info is ./updater/gup.xml
1. GUP.exe sends HTTP/1.1 GET /params?version=1.0(for example) to http://www.riskfree.com.cn:8080/
2. A http service is deployed in http://www.riskfree.com.cn:8080/. It will compare the version in request
with the local version. If the local version is higher, it will update the xml info. And GUP.exe
will download the setup file if the response from server is updated.



How to verify the app?
---------------
The repo for the verify lib is
https://github.com/DaisyKid/libCryptoppVikey/tree/master