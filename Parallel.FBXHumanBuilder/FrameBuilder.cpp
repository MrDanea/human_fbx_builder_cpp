#include "FrameBuilder.h"
#include <iostream>

FrameBuilder::FrameBuilder() {
    _fbxManager = FbxManager::Create();
    if (!_fbxManager) {
        std::cerr << "Error: Unable to create FBX Manager!" << std::endl;
        return;
    }

    _fbxScene = FbxScene::Create(_fbxManager, "HumanScene");
    if (!_fbxScene) {
        std::cerr << "Error: Unable to create FBX Scene!" << std::endl;
        return;
    }
}

FrameBuilder::~FrameBuilder() {
    if (_fbxManager) {
        _fbxManager->Destroy();
    }
}

FbxNode* FrameBuilder::CreateBoneNode(const Point& start, const Point& end, const std::string& name) {
    FbxSkeleton* skeleton = FbxSkeleton::Create(_fbxManager, name.c_str());
    skeleton->SetSkeletonType(FbxSkeleton::eLimbNode);

    FbxNode* boneNode = FbxNode::Create(_fbxManager, name.c_str());
    boneNode->SetNodeAttribute(skeleton);

    FbxVector4 position((start.X + end.X) / 2, (start.Y + end.Y) / 2, (start.Z + end.Z) / 2);
    boneNode->LclTranslation.Set(position);

    return boneNode;
}

void FrameBuilder::SetupSkeleton(FbxNode* parentNode, const Bone& bone, const std::string& name) {
    FbxNode* boneNode = CreateBoneNode(bone.Start, bone.End, name);
    parentNode->AddChild(boneNode);
}

bool FrameBuilder::BuildHuman(const Frame& frame, const std::string& outputPath) {
    FbxNode* rootNode = _fbxScene->GetRootNode();

    HumanMap humanMap = frame.getHumanMap();

    SetupSkeleton(rootNode, Bone{ humanMap.Nose, humanMap.LeftEye }, "Nose_LeftEye");
    SetupSkeleton(rootNode, Bone{ humanMap.Nose, humanMap.RightEye }, "Nose_RightEye");
    SetupSkeleton(rootNode, Bone{ humanMap.LeftEye, humanMap.LeftEar }, "LeftEye_LeftEar");
    SetupSkeleton(rootNode, Bone{ humanMap.RightEye, humanMap.RightEar }, "RightEye_RightEar");
    SetupSkeleton(rootNode, Bone{ humanMap.LeftShoulder, humanMap.RightShoulder }, "LeftShoulder_RightShoulder");
    SetupSkeleton(rootNode, Bone{ humanMap.LeftShoulder, humanMap.LeftElbow }, "LeftShoulder_LeftElbow");
    SetupSkeleton(rootNode, Bone{ humanMap.RightShoulder, humanMap.RightElbow }, "RightShoulder_RightElbow");
    SetupSkeleton(rootNode, Bone{ humanMap.LeftElbow, humanMap.LeftWrist }, "LeftElbow_LeftWrist");
    SetupSkeleton(rootNode, Bone{ humanMap.RightElbow, humanMap.RightWrist }, "RightElbow_RightWrist");
    SetupSkeleton(rootNode, Bone{ humanMap.LeftHip, humanMap.RightHip }, "LeftHip_RightHip");
    SetupSkeleton(rootNode, Bone{ humanMap.LeftHip, humanMap.LeftKnee }, "LeftHip_LeftKnee");
    SetupSkeleton(rootNode, Bone{ humanMap.RightHip, humanMap.RightKnee }, "RightHip_RightKnee");
    SetupSkeleton(rootNode, Bone{ humanMap.LeftKnee, humanMap.LeftAnkle }, "LeftKnee_LeftAnkle");
    SetupSkeleton(rootNode, Bone{ humanMap.RightKnee, humanMap.RightAnkle }, "RightKnee_RightAnkle");

    FbxExporter* exporter = FbxExporter::Create(_fbxManager, "");
    if (!exporter->Initialize(outputPath.c_str(), -1, _fbxManager->GetIOSettings())) {
        std::cerr << "Error: Unable to initialize FBX exporter!" << std::endl;
        return false;
    }

    if (!exporter->Export(_fbxScene)) {
        std::cerr << "Error: Unable to export FBX scene!" << std::endl;
        return false;
    }

    exporter->Destroy();
    return true;
}