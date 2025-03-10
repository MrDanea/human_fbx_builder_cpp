#include "FrameString.h"

FrameString::FrameString() : name("Unnamed"), frameRate(30.0) {}

FrameString::FrameString(const std::string& name, double frameRate)
    : name(name), frameRate(frameRate) {
}

void FrameString::addFrame(const Frame& frame) {
    frames.push_back(frame);
}

void FrameString::addFrames(const std::vector<Frame>& newFrames) {
    frames.insert(frames.end(), newFrames.begin(), newFrames.end());
}

Frame FrameString::getFrame(size_t index) const {
    if (index >= frames.size()) {
        throw std::out_of_range("Frame index out of range");
    }
    return frames[index];
}

const std::vector<Frame>& FrameString::getAllFrames() const {
    return frames;
}

size_t FrameString::getFrameCount() const {
    return frames.size();
}

void FrameString::setFrameRate(double fps) {
    frameRate = fps;
}

double FrameString::getFrameRate() const {
    return frameRate;
}

void FrameString::setName(const std::string& newName) {
    name = newName;
}

std::string FrameString::getName() const {
    return name;
}

Frame FrameString::interpolateFrame(size_t frame1Index, size_t frame2Index, float ratio) {
    if (frame1Index >= frames.size() || frame2Index >= frames.size()) {
        throw std::out_of_range("Frame index out of range");
    }

    const Frame& frame1 = frames[frame1Index];
    const Frame& frame2 = frames[frame2Index];

    HumanMap interpolatedMap;
    HumanMap map1 = frame1.getHumanMap();
    HumanMap map2 = frame2.getHumanMap();

    // Interpolate each point in the HumanMap
    interpolatedMap.Nose = interpolatePoint(map1.Nose, map2.Nose, ratio);
    interpolatedMap.LeftEye = interpolatePoint(map1.LeftEye, map2.LeftEye, ratio);
    interpolatedMap.RightEye = interpolatePoint(map1.RightEye, map2.RightEye, ratio);
    interpolatedMap.LeftEar = interpolatePoint(map1.LeftEar, map2.LeftEar, ratio);
    interpolatedMap.RightEar = interpolatePoint(map1.RightEar, map2.RightEar, ratio);
    interpolatedMap.LeftShoulder = interpolatePoint(map1.LeftShoulder, map2.LeftShoulder, ratio);
    interpolatedMap.RightShoulder = interpolatePoint(map1.RightShoulder, map2.RightShoulder, ratio);
    interpolatedMap.LeftElbow = interpolatePoint(map1.LeftElbow, map2.LeftElbow, ratio);
    interpolatedMap.RightElbow = interpolatePoint(map1.RightElbow, map2.RightElbow, ratio);
    interpolatedMap.LeftWrist = interpolatePoint(map1.LeftWrist, map2.LeftWrist, ratio);
    interpolatedMap.RightWrist = interpolatePoint(map1.RightWrist, map2.RightWrist, ratio);
    interpolatedMap.LeftHip = interpolatePoint(map1.LeftHip, map2.LeftHip, ratio);
    interpolatedMap.RightHip = interpolatePoint(map1.RightHip, map2.RightHip, ratio);
    interpolatedMap.LeftKnee = interpolatePoint(map1.LeftKnee, map2.LeftKnee, ratio);
    interpolatedMap.RightKnee = interpolatePoint(map1.RightKnee, map2.RightKnee, ratio);
    interpolatedMap.LeftAnkle = interpolatePoint(map1.LeftAnkle, map2.LeftAnkle, ratio);
    interpolatedMap.RightAnkle = interpolatePoint(map1.RightAnkle, map2.RightAnkle, ratio);

    return Frame(interpolatedMap);
}

Point3D FrameString::interpolatePoint(const Point3D& p1, const Point3D& p2, float ratio) {
    Point3D result;
    result.x = p1.x + (p2.x - p1.x) * ratio;
    result.y = p1.y + (p2.y - p1.y) * ratio;
    result.z = p1.z + (p2.z - p1.z) * ratio;
    return result;
}

void FrameString::insertFrame(size_t position, const Frame& frame) {
    if (position > frames.size()) {
        throw std::out_of_range("Insert position out of range");
    }
    frames.insert(frames.begin() + position, frame);
}

void FrameString::removeFrame(size_t position) {
    if (position >= frames.size()) {
        throw std::out_of_range("Remove position out of range");
    }
    frames.erase(frames.begin() + position);
}

void FrameString::clearFrames() {
    frames.clear();
}

bool FrameString::exportFrame(size_t index, const std::string& outputPath) {
    if (index >= frames.size()) {
        return false;
    }
    return builder.BuildHuman(frames[index], outputPath);
}

bool FrameString::exportAnimation(const std::string& outputPath) {
    return builder.BuildHumanAnimation(frames, outputPath, frameRate);
}

FrameString FrameString::createSubSequence(size_t startIndex, size_t endIndex, const std::string& newName) {
    if (startIndex >= frames.size() || endIndex >= frames.size() || startIndex > endIndex) {
        throw std::out_of_range("Invalid sub-sequence range");
    }

    FrameString subSequence(newName.empty() ? name + "_sub" : newName, frameRate);
    for (size_t i = startIndex; i <= endIndex; i++) {
        subSequence.addFrame(frames[i]);
    }

    return subSequence;
}

void FrameString::merge(const FrameString& other) {
    addFrames(other.getAllFrames());
}

void FrameString::reverseFrames() {
    std::reverse(frames.begin(), frames.end());
}

void FrameString::loopFrames(size_t repetitions) {
    if (frames.empty() || repetitions <= 1) {
        return;
    }

    size_t originalSize = frames.size();
    frames.reserve(originalSize * repetitions);

    for (size_t i = 1; i < repetitions; i++) {
        for (size_t j = 0; j < originalSize; j++) {
            frames.push_back(frames[j]);
        }
    }
}

FrameString FrameString::createMotion(const Frame& startFrame, const Frame& endFrame,
    size_t frameCount, const std::string& name) {
    FrameString motion(name);

    // Add the start frame
    motion.addFrame(startFrame);

    // Create intermediate frames
    for (size_t i = 1; i < frameCount - 1; i++) {
        float ratio = static_cast<float>(i) / (frameCount - 1);

        HumanMap startMap = startFrame.getHumanMap();
        HumanMap endMap = endFrame.getHumanMap();
        HumanMap interpolatedMap;

        // Interpolate each point
        interpolatedMap.Nose = motion.interpolatePoint(startMap.Nose, endMap.Nose, ratio);
        interpolatedMap.LeftEye = motion.interpolatePoint(startMap.LeftEye, endMap.LeftEye, ratio);
        interpolatedMap.RightEye = motion.interpolatePoint(startMap.RightEye, endMap.RightEye, ratio);
        interpolatedMap.LeftEar = motion.interpolatePoint(startMap.LeftEar, endMap.LeftEar, ratio);
        interpolatedMap.RightEar = motion.interpolatePoint(startMap.RightEar, endMap.RightEar, ratio);
        interpolatedMap.LeftShoulder = motion.interpolatePoint(startMap.LeftShoulder, endMap.LeftShoulder, ratio);
        interpolatedMap.RightShoulder = motion.interpolatePoint(startMap.RightShoulder, endMap.RightShoulder, ratio);
        interpolatedMap.LeftElbow = motion.interpolatePoint(startMap.LeftElbow, endMap.LeftElbow, ratio);
        interpolatedMap.RightElbow = motion.interpolatePoint(startMap.RightElbow, endMap.RightElbow, ratio);
        interpolatedMap.LeftWrist = motion.interpolatePoint(startMap.LeftWrist, endMap.LeftWrist, ratio);
        interpolatedMap.RightWrist = motion.interpolatePoint(startMap.RightWrist, endMap.RightWrist, ratio);
        interpolatedMap.LeftHip = motion.interpolatePoint(startMap.LeftHip, endMap.LeftHip, ratio);
        interpolatedMap.RightHip = motion.interpolatePoint(startMap.RightHip, endMap.RightHip, ratio);
        interpolatedMap.LeftKnee = motion.interpolatePoint(startMap.LeftKnee, endMap.LeftKnee, ratio);
        interpolatedMap.RightKnee = motion.interpolatePoint(startMap.RightKnee, endMap.RightKnee, ratio);
        interpolatedMap.LeftAnkle = motion.interpolatePoint(startMap.LeftAnkle, endMap.LeftAnkle, ratio);
        interpolatedMap.RightAnkle = motion.interpolatePoint(startMap.RightAnkle, endMap.RightAnkle, ratio);

        motion.addFrame(Frame(interpolatedMap));
    }

    // Add the end frame
    motion.addFrame(endFrame);

    return motion;
}