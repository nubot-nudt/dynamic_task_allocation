// Auto-generated. Do not edit!

// (in-package nubot_common.msg)


"use strict";

const _serializer = _ros_msg_utils.Serialize;
const _arraySerializer = _serializer.Array;
const _deserializer = _ros_msg_utils.Deserialize;
const _arrayDeserializer = _deserializer.Array;
const _finder = _ros_msg_utils.Find;
const _getByteLength = _ros_msg_utils.getByteLength;
let Point2d = require('./Point2d.js');
let PPoint = require('./PPoint.js');
let std_msgs = _finder('std_msgs');

//-----------------------------------------------------------

class BallInfo {
  constructor(initObj={}) {
    if (initObj === null) {
      // initObj === null is a special case for deserialization where we don't initialize fields
      this.header = null;
      this.ballinfostate = null;
      this.pos = null;
      this.real_pos = null;
      this.velocity = null;
      this.pos_known = null;
      this.velocity_known = null;
    }
    else {
      if (initObj.hasOwnProperty('header')) {
        this.header = initObj.header
      }
      else {
        this.header = new std_msgs.msg.Header();
      }
      if (initObj.hasOwnProperty('ballinfostate')) {
        this.ballinfostate = initObj.ballinfostate
      }
      else {
        this.ballinfostate = 0;
      }
      if (initObj.hasOwnProperty('pos')) {
        this.pos = initObj.pos
      }
      else {
        this.pos = new Point2d();
      }
      if (initObj.hasOwnProperty('real_pos')) {
        this.real_pos = initObj.real_pos
      }
      else {
        this.real_pos = new PPoint();
      }
      if (initObj.hasOwnProperty('velocity')) {
        this.velocity = initObj.velocity
      }
      else {
        this.velocity = new Point2d();
      }
      if (initObj.hasOwnProperty('pos_known')) {
        this.pos_known = initObj.pos_known
      }
      else {
        this.pos_known = false;
      }
      if (initObj.hasOwnProperty('velocity_known')) {
        this.velocity_known = initObj.velocity_known
      }
      else {
        this.velocity_known = false;
      }
    }
  }

  static serialize(obj, buffer, bufferOffset) {
    // Serializes a message object of type BallInfo
    // Serialize message field [header]
    bufferOffset = std_msgs.msg.Header.serialize(obj.header, buffer, bufferOffset);
    // Serialize message field [ballinfostate]
    bufferOffset = _serializer.int32(obj.ballinfostate, buffer, bufferOffset);
    // Serialize message field [pos]
    bufferOffset = Point2d.serialize(obj.pos, buffer, bufferOffset);
    // Serialize message field [real_pos]
    bufferOffset = PPoint.serialize(obj.real_pos, buffer, bufferOffset);
    // Serialize message field [velocity]
    bufferOffset = Point2d.serialize(obj.velocity, buffer, bufferOffset);
    // Serialize message field [pos_known]
    bufferOffset = _serializer.bool(obj.pos_known, buffer, bufferOffset);
    // Serialize message field [velocity_known]
    bufferOffset = _serializer.bool(obj.velocity_known, buffer, bufferOffset);
    return bufferOffset;
  }

  static deserialize(buffer, bufferOffset=[0]) {
    //deserializes a message object of type BallInfo
    let len;
    let data = new BallInfo(null);
    // Deserialize message field [header]
    data.header = std_msgs.msg.Header.deserialize(buffer, bufferOffset);
    // Deserialize message field [ballinfostate]
    data.ballinfostate = _deserializer.int32(buffer, bufferOffset);
    // Deserialize message field [pos]
    data.pos = Point2d.deserialize(buffer, bufferOffset);
    // Deserialize message field [real_pos]
    data.real_pos = PPoint.deserialize(buffer, bufferOffset);
    // Deserialize message field [velocity]
    data.velocity = Point2d.deserialize(buffer, bufferOffset);
    // Deserialize message field [pos_known]
    data.pos_known = _deserializer.bool(buffer, bufferOffset);
    // Deserialize message field [velocity_known]
    data.velocity_known = _deserializer.bool(buffer, bufferOffset);
    return data;
  }

  static getMessageSize(object) {
    let length = 0;
    length += std_msgs.msg.Header.getMessageSize(object.header);
    return length + 30;
  }

  static datatype() {
    // Returns string type for a message object
    return 'nubot_common/BallInfo';
  }

  static md5sum() {
    //Returns md5sum for a message object
    return '06211c2a8d639c68390f487a28e6a33a';
  }

  static messageDefinition() {
    // Returns full string definition for message
    return `
    Header header
    int32     ballinfostate
    Point2d   pos
    PPoint    real_pos
    Point2d   velocity
    bool      pos_known
    bool      velocity_known
    
    
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
    MSG: nubot_common/Point2d
    float32 x
    float32 y
    
    ================================================================================
    MSG: nubot_common/PPoint
    float32 angle
    float32 radius
    
    `;
  }

  static Resolve(msg) {
    // deep-construct a valid message object instance of whatever was passed in
    if (typeof msg !== 'object' || msg === null) {
      msg = {};
    }
    const resolved = new BallInfo(null);
    if (msg.header !== undefined) {
      resolved.header = std_msgs.msg.Header.Resolve(msg.header)
    }
    else {
      resolved.header = new std_msgs.msg.Header()
    }

    if (msg.ballinfostate !== undefined) {
      resolved.ballinfostate = msg.ballinfostate;
    }
    else {
      resolved.ballinfostate = 0
    }

    if (msg.pos !== undefined) {
      resolved.pos = Point2d.Resolve(msg.pos)
    }
    else {
      resolved.pos = new Point2d()
    }

    if (msg.real_pos !== undefined) {
      resolved.real_pos = PPoint.Resolve(msg.real_pos)
    }
    else {
      resolved.real_pos = new PPoint()
    }

    if (msg.velocity !== undefined) {
      resolved.velocity = Point2d.Resolve(msg.velocity)
    }
    else {
      resolved.velocity = new Point2d()
    }

    if (msg.pos_known !== undefined) {
      resolved.pos_known = msg.pos_known;
    }
    else {
      resolved.pos_known = false
    }

    if (msg.velocity_known !== undefined) {
      resolved.velocity_known = msg.velocity_known;
    }
    else {
      resolved.velocity_known = false
    }

    return resolved;
    }
};

module.exports = BallInfo;
