#pragma once
#include "HumanMap.h"
#include <fbxsdk.h>

class FrameBuilder {
public:
    FrameBuilder();
    ~FrameBuilder();

    bool BuildHuman(const Frame& frame, const std::string& outputPath);

private:
    FbxManager* _fbxManager;
    FbxScene* _fbxScene;

    FbxNode* CreateBoneNode(const Point& start, const Point& end, const std::string& name);
    void SetupSkeleton(FbxNode* parentNode, const Bone& bone, const std::string& name);
};