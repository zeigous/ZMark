local GHRLen = 14
local PHTLen = (1 << GHRLen)
local GHRXorMask = PHTLen - 1

local PHT = {}
local GHR = 0

for i=1,PHTLen do
    PHT[i] = 0
end

function reset()
    for i=1,PHTLen do
        PHT[i] = 0
    end
    return 0 -- success
end

function predict(PC)
    local maskedPC = GHRXorMask & PC
    local maskedGHR = GHR & GHRXorMask

    local index = (maskedPC ~ maskedGHR) + 1 -- convert from 0 to 1 based indexing
    local prediction = PHT[index]

    if prediction < 2 then
        return 0
    end
    return 1 -- taken
end

function update(PC, branchResult, prediction)
    local maskedPC = GHRXorMask & PC
    local maskedGHR = GHR & GHRXorMask

    local index = (maskedPC ~ maskedGHR) + 1 -- convert from 0 to 1 based indexing
    local prediction = PHT[index]

    if branchResult == 1 then
        if prediction < 3 then
            prediction = prediction + 1
        end
    else 
        if prediction > 0 then
            prediction = prediction - 1
        end
    end

    PHT[index] = prediction

    GHR = ((GHR << 1) & GHRXorMask) + branchResult

    return 0 -- success
end