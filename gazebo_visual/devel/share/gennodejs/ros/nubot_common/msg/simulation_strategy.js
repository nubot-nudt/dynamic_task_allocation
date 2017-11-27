// Auto-generated. Do not edit!

// (in-package nubot_common.msg)


"use strict";

const _serializer = _ros_msg_utils.Serialize;
const _arraySerializer = _serializer.Array;
const _deserializer = _ros_msg_utils.Deserialize;
const _arrayDeserializer = _deserializer.Array;
const _finder = _ros_msg_utils.Find;
const _getByteLength = _ros_msg_utils.getByteLength;
let StrategyInfo = require('./StrategyInfo.js');

//-----------------------------------------------------------

class simulation_strategy {
  constructor(initObj={}) {
    if (initObj === null) {
      // initObj === null is a special case for deserialization where we don't initialize fields
      this.strategy_msgs = null;
    }
    else {
      if (initObj.hasOwnProperty('strategy_msgs')) {
        this.strategy_msgs = initObj.strategy_msgs
      }
      else {
        this.strategy_msgs = [];
      }
    }
  }

  static serialize(obj, buffer, bufferOffset) {
    // Serializes a message object of type simulation_strategy
    // Serialize message field [strategy_msgs]
    // Serialize the length for message field [strategy_msgs]
    bufferOffset = _serializer.uint32(obj.strategy_msgs.length, buffer, bufferOffset);
    obj.strategy_msgs.forEach((val) => {
      bufferOffset = StrategyInfo.serialize(val, buffer, bufferOffset);
    });
    return bufferOffset;
  }

  static deserialize(buffer, bufferOffset=[0]) {
    //deserializes a message object of type simulation_strategy
    let len;
    let data = new simulation_strategy(null);
    // Deserialize message field [strategy_msgs]
    // Deserialize array length for message field [strategy_msgs]
    len = _deserializer.uint32(buffer, bufferOffset);
    data.strategy_msgs = new Array(len);
    for (let i = 0; i < len; ++i) {
      data.strategy_msgs[i] = StrategyInfo.deserialize(buffer, bufferOffset)
    }
    return data;
  }

  static getMessageSize(object) {
    let length = 0;
    object.strategy_msgs.forEach((val) => {
      length += StrategyInfo.getMessageSize(val);
    });
    return length + 4;
  }

  static datatype() {
    // Returns string type for a message object
    return 'nubot_common/simulation_strategy';
  }

  static md5sum() {
    //Returns md5sum for a message object
    return '1d84999556ec502fdeaed67902dd635f';
  }

  static messageDefinition() {
    // Returns full string definition for message
    return `
    StrategyInfo[] strategy_msgs
    
    ================================================================================
    MSG: nubot_common/StrategyInfo
    Header   header
    int32    AgentID
    int32    targetNum1
    int32    targetNum2
    int32    targetNum3
    int32    targetNum4
    int32    staticpassNum
    int32    staticcatchNum
    uint32   role
    uint32   action
    bool     is_dribble
    bool     is_kickoff
    float32  role_time
    PassCommands  pass_cmd
    
    
    
    
    ================================================================================
    MSG: std_msgs/Header
    # Standard metadata for higher-level stamped data types.
    # This is generally used to communicate timestamped data 
    # in a particular coordinate frame.
    # 
    # sequence ID: consecutively increasing ID 
    uint32 seq
    #Two-integer timestamp that is expressed as:
    # * stamp.sec: seconds (stamp_secs) since epoch (in Python the variable is called 'secs')
    # * stamp.nsec: nanoseconds since stamp_secs (in Python the variable is called 'nsecs')
    # time-handling sugar is provided by the client library
    time stamp
    #Frame this data is associated with
    # 0: no frame
    # 1: global frame
    string frame_id
    
    ================================================================================
    MSG: nubot_common/PassCommands
    uint32  pass_id
    uint32  catch_id
    Point2d pass_pt
    Point2d catch_pt
    bool    is_passout
    bool    is_dynamic_pass
    bool    is_static_pass
    bool    is_valid
     
    
    ================================================================================
    MSG: nubot_common/Point2d
    float32 x
    float32 y
    
    `;
  }

  static Resolve(msg) {
    // deep-construct a valid message object instance of whatever was passed in
    if (typeof msg !== 'object' || msg === null) {
      msg = {};
    }
    const resolved = new simulation_strategy(null);
    if (msg.strategy_msgs !== undefined) {
      resolved.strategy_msgs = new Array(msg.strategy_msgs.length);
      for (let i = 0; i < resolved.strategy_msgs.length; ++i) {
        resolved.strategy_msgs[i] = StrategyInfo.Resolve(msg.strategy_msgs[i]);
      }
    }
    else {
      resolved.strategy_msgs = []
    }

    return resolved;
    }
};

module.exports = simulation_strategy;
