#pragma once

#include <vector>
#include <string>
#include <memory>
#include "HumanMap.h"
#include "FrameBuilder.h"

class FrameString {
private:
    std::vector<Frame> frames;
    std::string name;
    double frameRate;
    FrameBuilder builder;

public:
    // Constructors
    FrameString();
    FrameString(const std::string& name, double frameRate = 30.0);

    // Add a single frame to the collection
    void addFrame(const Frame& frame);

    // Add multiple frames at once
    void addFrames(const std::vector<Frame>& newFrames);

    // Get a specific frame by index
    Frame getFrame(size_t index) const;

    // Get all frames
    const std::vector<Frame>& getAllFrames() const;

    // Get the number of frames
    size_t getFrameCount() const;

    // Set/Get frame rate
    void setFrameRate(double fps);
    double getFrameRate() const;

    // Set/Get name
    void setName(const std::string& newName);
    std::string getName() const;

    // Create a new frame with interpolated positions between two existing frames
    Frame interpolateFrame(size_t frame1Index, size_t frame2Index, float ratio);

    // Insert a frame at a specific position
    void insertFrame(size_t position, const Frame& frame);

    // Remove a frame at a specific position
    void removeFrame(size_t position);

    // Clear all frames
    void clearFrames();

    // Export a single frame to FBX
    bool exportFrame(size_t index, const std::string& outputPath);

    // Export the entire animation to FBX
    bool exportAnimation(const std::string& outputPath);

    // Create a sub-sequence from this FrameString
    FrameString createSubSequence(size_t startIndex, size_t endIndex, const std::string& newName = "");

    // Merge with another FrameString (appends frames)
    void merge(const FrameString& other);

    // Utility methods for animation manipulation
    void reverseFrames();
    void loopFrames(size_t repetitions);

    // Utility to create a simple motion between two poses
    static FrameString createMotion(const Frame& startFrame, const Frame& endFrame,
        size_t frameCount, const std::string& name = "Motion");
};