#include "HumanMap.h"
#include <array>
#include <iostream>

Frame::Frame(const HumanMap& humanmap) : _humanMap(humanmap) {
    bones = {
        Bone{humanmap.Nose, humanmap.LeftEye},
        Bone{humanmap.Nose, humanmap.RightEye},
        Bone{humanmap.LeftEye, humanmap.LeftEar},
        Bone{humanmap.RightEye, humanmap.RightEar},
        Bone{humanmap.RightEye, humanmap.LeftEye},
        Bone{humanmap.LeftShoulder, humanmap.RightShoulder},
        Bone{humanmap.LeftShoulder, humanmap.LeftElbow},
        Bone{humanmap.RightShoulder, humanmap.RightElbow},
        Bone{humanmap.LeftShoulder, humanmap.LeftEar},
        Bone{humanmap.RightShoulder, humanmap.RightEar},
        Bone{humanmap.LeftElbow, humanmap.LeftWrist},
        Bone{humanmap.RightElbow, humanmap.RightWrist},
        Bone{humanmap.LeftHip, humanmap.RightHip},
        Bone{humanmap.LeftHip, humanmap.LeftKnee},
        Bone{humanmap.RightHip, humanmap.RightKnee},
        Bone{humanmap.LeftKnee, humanmap.LeftAnkle},
        Bone{humanmap.RightKnee, humanmap.RightAnkle},
        Bone{humanmap.LeftShoulder, humanmap.LeftHip},
        Bone{humanmap.RightShoulder, humanmap.RightHip}
    };
}
HumanMap Frame::getHumanMap() const {
	return _humanMap;
}
void Frame::printBones() const {
    for (const auto& bone : bones) {
        std::cout << "Bone from (" << bone.Start.X << ", " << bone.Start.Y << ", " << bone.Start.Z << ") to ("
            << bone.End.X << ", " << bone.End.Y << ", " << bone.End.Z << ")\n";
    }
}