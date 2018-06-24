tar -cvf RoboArmBuild.tar.gz RoboArm
scp ../RoboArmBuild.tar.gz pi@10.0.0.2:/
ssh pi@10.0.0.2 "tar -xf RoboArmBuild.tar.gz && cd RoboArmBuild && chmod a+x *"
ssh pi@10.0.0.2 "cd RoboArmBuild && ./build.sh"