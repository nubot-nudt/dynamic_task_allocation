// Auto-generated. Do not edit!

// (in-package nubot_common.msg)


"use strict";

const _serializer = _ros_msg_utils.Serialize;
const _arraySerializer = _serializer.Array;
const _deserializer = _ros_msg_utils.Deserialize;
const _arrayDeserializer = _deserializer.Array;
const _finder = _ros_msg_utils.Find;
const _getByteLength = _ros_msg_utils.getByteLength;
let Point3d = require('./Point3d.js');
let std_msgs = _finder('std_msgs');

//-----------------------------------------------------------

class BallInfo3d {
  constructor(initObj={}) {
    if (initObj === null) {
      // initObj === null is a special case for deserialization where we don't initialize fields
      this.header = null;
      this.pos = null;
      this.velocity = null;
      this.pos_known_3d = null;
      this.pos_known_2d = null;
      this.velocity_known = null;
    }
    else {
      if (initObj.hasOwnProperty('header')) {
        this.header = initObj.header
      }
      else {
        this.header = new std_msgs.msg.Header();
      }
      if (initObj.hasOwnProperty('pos')) {
        this.pos = initObj.pos
      }
      else {
        this.pos = new Point3d();
      }
      if (initObj.hasOwnProperty('velocity')) {
        this.velocity = initObj.velocity
      }
      else {
        this.velocity = new Point3d();
      }
      if (initObj.hasOwnProperty('pos_known_3d')) {
        this.pos_known_3d = initObj.pos_known_3d
      }
      else {
        this.pos_known_3d = false;
      }
      if (initObj.hasOwnProperty('pos_known_2d')) {
        this.pos_known_2d = initObj.pos_known_2d
      }
      else {
        this.pos_known_2d = false;
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
    // Serializes a message object of type BallInfo3d
    // Serialize message field [header]
    bufferOffset = std_msgs.msg.Header.serialize(obj.header, buffer, bufferOffset);
    // Serialize message field [pos]
    bufferOffset = Point3d.serialize(obj.pos, buffer, bufferOffset);
    // Serialize message field [velocity]
    bufferOffset = Point3d.serialize(obj.velocity, buffer, bufferOffset);
    // Serialize message field [pos_known_3d]
    bufferOffset = _serializer.bool(obj.pos_known_3d, buffer, bufferOffset);
    // Serialize message field [pos_known_2d]
    bufferOffset = _serializer.bool(obj.pos_known_2d, buffer, bufferOffset);
    // Serialize message field [velocity_known]
    bufferOffset = _serializer.bool(obj.velocity_known, buffer, bufferOffset);
    return bufferOffset;
  }

  static deserialize(buffer, bufferOffset=[0]) {
    //deserializes a message object of type BallInfo3d
    let len;
    let data = new BallInfo3d(null);
    // Deserialize message field [header]
    data.header = std_msgs.msg.Header.deserialize(buffer, bufferOffset);
    // Deserialize message field [pos]
    data.pos = Point3d.deserialize(buffer, bufferOffset);
    // Deserialize message field [velocity]
    data.velocity = Point3d.deserialize(buffer, bufferOffset);
    // Deserialize message field [pos_known_3d]
    data.pos_known_3d = _deserializer.bool(buffer, bufferOffset);
    // Deserialize message field [pos_known_2d]
    data.pos_known_2d = _deserializer.bool(buffer, bufferOffset);
    // Deserialize message field [velocity_known]
    data.velocity_known = _deserializer.bool(buffer, bufferOffset);
    return data;
  }

  static getMessageSize(object) {
    let length = 0;
    length += std_msgs.msg.Header.getMessageSize(object.header);
    return length + 27;
  }

  static datatype() {
    // Returns string type for a message object
    return 'nubot_common/BallInfo3d';
  }

  static md5sum() {
    //Returns md5sum for a message object
    return '6634a529c2fba000f06cf99f5ab31312';
  }

  static messageDefinition() {
    // Returns full string definition for message
    return `
    Header header
    Point3d   pos
    Point3d   velocity
    bool      pos_known_3d
    bool      pos_known_2d
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
    MSG: nubot_common/Point3d
    float32 x
    float32 y
    float32 z
    
    `;
  }

  static Resolve(msg) {
    // deep-construct a valid message object instance of whatever was passed in
    if (typeof msg !== 'object' || msg === null) {
      msg = {};
    }
    const resolved = new BallInfo3d(null);
    if (msg.header !== undefined) {
      resolved.header = std_msgs.msg.Header.Resolve(msg.header)
    }
    else {
      resolved.header = new std_msgs.msg.Header()
    }

    if (msg.pos !== undefined) {
      resolved.pos = Point3d.Resolve(msg.pos)
    }
    else {
      resolved.pos = new Point3d()
    }

    if (msg.velocity !== undefined) {
      resolved.velocity = Point3d.Resolve(msg.velocity)
    }
    else {
      resolved.velocity = new Point3d()
    }

    if (msg.pos_known_3d !== undefined) {
      resolved.pos_known_3d = msg.pos_known_3d;
    }
    else {
      resolved.pos_known_3d = false
    }

    if (msg.pos_known_2d !== undefined) {
      resolved.pos_known_2d = msg.pos_known_2d;
    }
    else {
      resolved.pos_known_2d = false
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

module.exports = BallInfo3d;
