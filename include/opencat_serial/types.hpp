#pragma once
#include <cstdint>
#include <iostream>
#include <vector>

namespace OpenCat
{
/**
 * @brief list all commands available
 **/
enum Command : uint8_t
{
    /** Control Commands */
    SHUT_DOWN,                // rest and shutdown all servos
    SWITCH_GYRO,              // switch whether to use IMU data
    PAUSE_MOTION,             // TODO: difference between shutdown?
    CALIBRATE,                // Calibration mode
    SWITCH_RECOVERING,        // TODO: check if this can be disabled
    REPEAT_SKILL,             // repeat last called skill
    PLAY_CUSTOM_SKILL,        // play custom defined skill
    MOVE_JOINT_SEQUENCE,      // move joints in sequence
    MOVE_JOINTS_SIMULTANEOUS, // move joints all at once
    SET_JOINTS,               // set all joints at once
    PLAY_MELODY,              // play built-in melody
    PLAY_CUSTOM_SOUND,        // play the cutom provided sound

    /** Gaits */
    STEPPING,    // stepping on the same spot
    BACK,        // going back
    BACK_LEFT,   // going back and left
    BACK_RIGHT,  // going back and right
    CRAWL,       // crawl forward
    CRAWL_LEFT,  // crawl left
    CRAWL_RIGHT, // crawl right
    WALK,        // walk forward
    WALK_LEFT,   // walk left
    WALK_RIGHT,  // walk right
    TROT,        // trot forward
    TROT_LEFT,   // trot left
    TROT_RIGHT,  // trot right
    BOUND,       // not recommended

    /** Postures */
    BALANCE,    // balancing mode
    BUTT_UP,    // raise hip
    CALIB_POSE, // Calibration pose, make easy to calibrate joints
    REST,       // rest mode TODO: difference between SHUT_DOWN
    SIT,
    SLEEP,
    STRETCH,
    ZERO, // template for designing new posture

    /** Behavior */
    CHECK_AROUND,
    GREETING,
    PEE,
    PUSH_UP,
    MIMIC_DEATH,
    BACK_FLIP
};

// alias for command arguments
using TaskArgs = std::vector<int16_t>;

/**
 * @brief task structure defining a task
 * @param cmd: %Command enum type specifying command
 * @param arguments: %vector storing possible parameter
 * @param delay: delay in seconds after finishing command
 **/
struct Task
{
    Task(Command _cmd) : cmd(_cmd), arguments{}, delay(0){};
    Task(Command _cmd, float _delay) : cmd(_cmd), arguments{}, delay(_delay){};
    Task(Command _cmd, TaskArgs _args, float _delay)
        : cmd(_cmd), arguments{_args.begin(), _args.end()}, delay(_delay){};
    Command cmd;
    TaskArgs arguments;
    float delay;
};

const std::vector<std::string> CMD_NAME{
    /** Control Commands */
    "d",   // SHUT_DOWN
    "g",   // SWITCH_GYRO
    "p",   // PAUSE_MOTION
    "c",   // CALIBRATE
    "krc", // RECOVERING
    "T",   // REPEAT_SKILL
    "K",   // PLAY_CUSTOM_SKILL
    "M",   // MOVE_JOINT_SEQUENCE
    "I",   // MOVE_JOINTS_SIMULTANEOUS
    "L",   // SET_JOINTS
    "o",   // PLAY_MELODY
    "B",   // PLAY_CUSTOM_SOUND

    /** Gaits */
    "kvt",  // STEPPING
    "kbk",  // BACK
    "kbkL", // BACK_LEFT
    "kbkR", // BACK_RIGHT
    "kcrF", // CRAWL
    "kcrL", // CRAWL_LEFT
    "kcrR", // CRAWL_RIGHT
    "kwkF", // WALK
    "kwkL", // WALK_LEFT
    "kwkR", // WALK_RIGHT
    "ktrF", // TROT
    "ktrL", // TROT_LEFT
    "ktrR", // TROT_RIGHT
    "kbdF", // BOUND

    /** Postures */
    "kbalance", // BALANCE
    "kbuttUp",  // BUTT_UP
    "kcalib",   // CALIB_POSE
    "krest",    // REST
    "ksit",     // SIT
    "ksleep",   // SLEEP
    "kstr",     // STRETCH
    "kzero",    // ZERO

    /** Behavior */
    "kck",  // CHECK_AROUND
    "khi",  // GREETING
    "kpee", // PEE
    "kpu",  // PUSH_UP
    "kpd",  // MIMIC_DEATH
    "kbf"   // BACK_FLIP
};

const std::vector<std::string> CMD_DESCRIPTION{
    /** Control Commands */
    "shut down",            // SHUT_DOWN
    "switch IMU",           // SWITCH_GYRO
    "pause motion",         // PAUSE_MOTION
    "calibrate",            // CALIBRATE
    "recovering",           // RECOVERING
    "repeat custom skill",  // REPEAT_SKILL
    "play custom skill",    // PLAY_CUSTOM_SKILL
    "move joint sequence",  // MOVE_JOINT_SEQUENCE
    "index and set joints", // MOVE_JOINTS_SIMULTANEOUS
    "set all joints",       // SET_JOINTS
    "play built-in melody", // PLAY_MELODY
    "play custom melody",   // PLAY_CUSTOM_SOUND

    /** Gaits */
    "stepping",             // STEPPING
    "going back",           // BACK
    "going back and left",  // BACK_LEFT
    "going back and right", // BACK_RIGHT
    "crawl",                // CRAWL
    "crawl left",           // CRAWL_LEFT
    "crawl right",          // CRAWL_RIGHT
    "walk",                 // WALK
    "walk left",            // WALK_LEFT
    "walk right",           // WALK_RIGHT
    "trot",                 // TROT
    "trot left",            // TROT_LEFT
    "trot right",           // TROT_RIGHT
    "bound",                // BOUND

    /** Postures */
    "balance",          // BALANCE
    "butt up",          // BUTT_UP
    "calibration pose", // CALIB_POSE
    "rest",             // REST
    "sit",              // SIT
    "sleep",            // SLEEP
    "stretch",          // STRETCH
    "zero",             // ZERO

    /** Behavior */
    "check around", // CHECK_AROUND
    "greeting",     // GREETING
    "pee",          // PEE
    "push up",      // PUSH_UP
    "mimic death",  // MIMIC_DEATH
    "back flip"     // BACK_FLIP
};
} // namespace OpenCat
