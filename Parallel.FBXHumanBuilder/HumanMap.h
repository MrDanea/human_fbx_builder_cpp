#pragma once
#include <array>
#include <iostream>
class Point {
public:
    double X;
    double Y;
    double Z;
};
class Bone {
public:
    Point Start;
    Point End;
};
class HumanMap {
public:
    Point Nose;
    Point LeftEye;
    Point RightEye;
    Point LeftEar;
    Point RightEar;
    Point LeftShoulder;
    Point RightShoulder;
    Point LeftElbow;
    Point RightElbow;
    Point LeftWrist;
    Point RightWrist;
    Point LeftHip;
    Point RightHip;
    Point LeftKnee;
    Point RightKnee;
    Point LeftAnkle;
    Point RightAnkle;
};
class Frame {
private:
    HumanMap _humanMap;
    std::array<Bone, 19> bones; 

public:
    Frame(const HumanMap& humanmap);
	HumanMap getHumanMap() const;
    void printBones() const;
};