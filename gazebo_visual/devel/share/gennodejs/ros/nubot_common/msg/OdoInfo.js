// Auto-generated. Do not edit!

// (in-package nubot_common.msg)


"use strict";

const _serializer = _ros_msg_utils.Serialize;
const _arraySerializer = _serializer.Array;
const _deserializer = _ros_msg_utils.Deserialize;
const _arrayDeserializer = _deserializer.Array;
const _finder = _ros_msg_utils.Find;
const _getByteLength = _ros_msg_utils.getByteLength;
let std_msgs = _finder('std_msgs');

//-----------------------------------------------------------

class OdoInfo {
  constructor(initObj={}) {
    if (initObj === null) {
      // initObj === null is a special case for deserialization where we don't initialize fields
      this.header = null;
      this.Vx = null;
      this.Vy = null;
      this.w = null;
      this.RobotStuck = null;
      this.PowerState = null;
    }
    else {
      if (initObj.hasOwnProperty('header')) {
        this.header = initObj.header
      }
      else {
        this.header = new std_msgs.msg.Header();
      }
      if (initObj.hasOwnProperty('Vx')) {
        this.Vx = initObj.Vx
      }
      else {
        this.Vx = 0.0;
      }
      if (initObj.hasOwnProperty('Vy')) {
        this.Vy = initObj.Vy
      }
      else {
        this.Vy = 0.0;
      }
      if (initObj.hasOwnProperty('w')) {
        this.w = initObj.w
      }
      else {
        this.w = 0.0;
      }
      if (initObj.hasOwnProperty('RobotStuck')) {
        this.RobotStuck = initObj.RobotStuck
      }
      else {
        this.RobotStuck = false;
      }
      if (initObj.hasOwnProperty('PowerState')) {
        this.PowerState = initObj.PowerState
      }
      else {
        this.PowerState = false;
      }
    }
  }

  static serialize(obj, buffer, bufferOffset) {
    // Serializes a message object of type OdoInfo
    // Serialize message field [header]
    bufferOffset = std_msgs.msg.Header.serialize(obj.header, buffer, bufferOffset);
    // Serialize message field [Vx]
    bufferOffset = _serializer.float32(obj.Vx, buffer, bufferOffset);
    // Serialize message field [Vy]
    bufferOffset = _serializer.float32(obj.Vy, buffer, bufferOffset);
    // Serialize message field [w]
    bufferOffset = _serializer.float32(obj.w, buffer, bufferOffset);
    // Serialize message field [RobotStuck]
    bufferOffset = _serializer.bool(obj.RobotStuck, buffer, bufferOffset);
    // Serialize message field [PowerState]
    bufferOffset = _serializer.bool(obj.PowerState, buffer, bufferOffset);
    return bufferOffset;
  }

  static deserialize(buffer, bufferOffset=[0]) {
    //deserializes a message object of type OdoInfo
    let len;
    let data = new OdoInfo(null);
    // Deserialize message field [header]
    data.header = std_msgs.msg.Header.deserialize(buffer, bufferOffset);
    // Deserialize message field [Vx]
    data.Vx = _deserializer.float32(buffer, bufferOffset);
    // Deserialize message field [Vy]
    data.Vy = _deserializer.float32(buffer, bufferOffset);
    // Deserialize message field [w]
    data.w = _deserializer.float32(buffer, bufferOffset);
    // Deserialize message field [RobotStuck]
    data.RobotStuck = _deserializer.bool(buffer, bufferOffset);
    // Deserialize message field [PowerState]
    data.PowerState = _deserializer.bool(buffer, bufferOffset);
    return data;
  }

  static getMessageSize(object) {
    let length = 0;
    length += std_msgs.msg.Header.getMessageSize(object.header);
    return length + 14;
  }

  static datatype() {
    // Returns string type for a message object
    return 'nubot_common/OdoInfo';
  }

  static md5sum() {
    //Returns md5sum for a message object
    return 'b4f534aa8c080899ef112a410cc2c113';
  }

  static messageDefinition() {
    // Returns full string definition for message
    return `
    Header  header
    float32 Vx
    float32 Vy
    float32 w
    bool    RobotStuck
    bool    PowerState
    
    
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
    
    `;
  }

  static Resolve(msg) {
    // deep-construct a valid message object instance of whatever was passed in
    if (typeof msg !== 'object' || msg === null) {
      msg = {};
    }
    const resolved = new OdoInfo(null);
    if (msg.header !== undefined) {
      resolved.header = std_msgs.msg.Header.Resolve(msg.header)
    }
    else {
      resolved.header = new std_msgs.msg.Header()
    }

    if (msg.Vx !== undefined) {
      resolved.Vx = msg.Vx;
    }
    else {
      resolved.Vx = 0.0
    }

    if (msg.Vy !== undefined) {
      resolved.Vy = msg.Vy;
    }
    else {
      resolved.Vy = 0.0
    }

    if (msg.w !== undefined) {
      resolved.w = msg.w;
    }
    else {
      resolved.w = 0.0
    }

    if (msg.RobotStuck !== undefined) {
      resolved.RobotStuck = msg.RobotStuck;
    }
    else {
      resolved.RobotStuck = false
    }

    if (msg.PowerState !== undefined) {
      resolved.PowerState = msg.PowerState;
    }
    else {
      resolved.PowerState = false
    }

    return resolved;
    }
};

module.exports = OdoInfo;
