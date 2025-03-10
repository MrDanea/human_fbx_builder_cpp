#include "FrameBuilder.h"
#include "HumanMap.h"

int main() {
    HumanMap humanMap;
    humanMap.Nose = { 0, 0, 0 };
    humanMap.LeftEye = { 1, 1, 1 };
    humanMap.RightEye = { 1, -1, 1 };
    humanMap.LeftEar = { 2, 2, 2 };
    humanMap.RightEar = { 2, -2, 2 };
    humanMap.LeftShoulder = { 3, 3, 3 };
    humanMap.RightShoulder = { 3, -3, 3 };
    humanMap.LeftElbow = { 4, 4, 4 };
    humanMap.RightElbow = { 4, -4, 4 };
    humanMap.LeftWrist = { 5, 5, 5 };
    humanMap.RightWrist = { 5, -5, 5 };
    humanMap.LeftHip = { 6, 6, 6 };
    humanMap.RightHip = { 6, -6, 6 };
    humanMap.LeftKnee = { 7, 7, 7 };
    humanMap.RightKnee = { 7, -7, 7 };
    humanMap.LeftAnkle = { 8, 8, 8 };
    humanMap.RightAnkle = { 8, -8, 8 };

    Frame frame(humanMap);

    FrameBuilder frameBuilder;
    if (frameBuilder.BuildHuman(frame, "output_human.fbx")) {
        std::cout << "Human model built successfully!" << std::endl;
    }
    else {
        std::cerr << "Failed to build human model!" << std::endl;
    }

    return 0;
}