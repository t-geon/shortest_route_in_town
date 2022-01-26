#ifndef RESULT_H
#define RESULT_H

// number of error 
enum Result
{
    Success = 0,

    InvalidAlgorithmName = 001,
    InvalidOptionName=003,
    FaildtoUpdatePath = 005,

    CommandFileNotExist = 100,
    LoadFileNotExist,

    VertexKeyNotExist = 200,
    InvalidVertexKey,
    GraphNotExist,
    InvalidAlgorithm,
    NegativeCycleDetected,

    NonDefinedCommand = 300,

};

#endif
