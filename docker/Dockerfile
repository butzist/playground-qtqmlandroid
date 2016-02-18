FROM rabits/qt:5.4-android

USER root

RUN apt-get -qq update && apt-get -qq install --fix-missing -y g++ && apt-get -qq clean
RUN echo "y" | /opt/android-sdk-linux/tools/android update sdk -u -a -t extra-android-support,extra-android-m2repository

USER user
