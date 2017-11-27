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
let Angle = require('./Angle.js');
let std_msgs = _finder('std_msgs');

//-----------------------------------------------------------

class RobotInfo {
  constructor(initObj={}) {
    if (initObj === null) {
      // initObj === null is a special case for deserialization where we don't initialize fields
      this.header = null;
      this.AgentID = null;
      this.pos = null;
      this.heading = null;
      this.vrot = null;
      this.vtrans = null;
      this.iskick = null;
      this.isvalid = null;
      this.isstuck = null;
      this.isdribble = null;
      this.current_role = null;
      this.role_time = null;
      this.target = null;
    }
    else {
      if (initObj.hasOwnProperty('header')) {
        this.header = initObj.header
      }
      else {
        this.header = new std_msgs.msg.Header();
      }
      if (initObj.hasOwnProperty('AgentID')) {
        this.AgentID = initObj.AgentID
      }
      else {
        this.AgentID = 0;
      }
      if (initObj.hasOwnProperty('pos')) {
        this.pos = initObj.pos
      }
      else {
        this.pos = new Point2d();
      }
      if (initObj.hasOwnProperty('heading')) {
        this.heading = initObj.heading
      }
      else {
        this.heading = new Angle();
      }
      if (initObj.hasOwnProperty('vrot')) {
        this.vrot = initObj.vrot
      }
      else {
        this.vrot = 0.0;
      }
      if (initObj.hasOwnProperty('vtrans')) {
        this.vtrans = initObj.vtrans
      }
      else {
        this.vtrans = new Point2d();
      }
      if (initObj.hasOwnProperty('iskick')) {
        this.iskick = initObj.iskick
      }
      else {
        this.iskick = false;
      }
      if (initObj.hasOwnProperty('isvalid')) {
        this.isvalid = initObj.isvalid
      }
      else {
        this.isvalid = false;
      }
      if (initObj.hasOwnProperty('isstuck')) {
        this.isstuck = initObj.isstuck
      }
      else {
        this.isstuck = false;
      }
      if (initObj.hasOwnProperty('isdribble')) {
        this.isdribble = initObj.isdribble
      }
      else {
        this.isdribble = false;
      }
      if (initObj.hasOwnProperty('current_role')) {
        this.current_role = initObj.current_role
      }
      else {
        this.current_role = 0;
      }
      if (initObj.hasOwnProperty('role_time')) {
        this.role_time = initObj.role_time
      }
      else {
        this.role_time = 0.0;
      }
      if (initObj.hasOwnProperty('target')) {
        this.target = initObj.target
      }
      else {
        this.target = new Point2d();
      }
    }
  }

  static serialize(obj, buffer, bufferOffset) {
    // Serializes a message object of type RobotInfo
    // Serialize message field [header]
    bufferOffset = std_msgs.msg.Header.serialize(obj.header, buffer, bufferOffset);
    // Serialize message field [AgentID]
    bufferOffset = _serializer.int32(obj.AgentID, buffer, bufferOffset);
    // Serialize message field [pos]
    bufferOffset = Point2d.serialize(obj.pos, buffer, bufferOffset);
    // Serialize message field [heading]
    bufferOffset = Angle.serialize(obj.heading, buffer, bufferOffset);
    // Serialize message field [vrot]
    bufferOffset = _serializer.float32(obj.vrot, buffer, bufferOffset);
    // Serialize message field [vtrans]
    bufferOffset = Point2d.serialize(obj.vtrans, buffer, bufferOffset);
    // Serialize message field [iskick]
    bufferOffset = _serializer.bool(obj.iskick, buffer, bufferOffset);
    // Serialize message field [isvalid]
    bufferOffset = _serializer.bool(obj.isvalid, buffer, bufferOffset);
    // Serialize message field [isstuck]
    bufferOffset = _serializer.bool(obj.isstuck, buffer, bufferOffset);
    // Serialize message field [isdribble]
    bufferOffset = _serializer.bool(obj.isdribble, buffer, bufferOffset);
    // Serialize message field [current_role]
    bufferOffset = _serializer.char(obj.current_role, buffer, bufferOffset);
    // Serialize message field [role_time]
    bufferOffset = _serializer.float32(obj.role_time, buffer, bufferOffset);
    // Serialize message field [target]
    bufferOffset = Point2d.serialize(obj.target, buffer, bufferOffset);
    return bufferOffset;
  }

  static deserialize(buffer, bufferOffset=[0]) {
    //deserializes a message object of type RobotInfo
    let len;
    let data = new RobotInfo(null);
    // Deserialize message field [header]
    data.header = std_msgs.msg.Header.deserialize(buffer, bufferOffset);
    // Deserialize message field [AgentID]
    data.AgentID = _deserializer.int32(buffer, bufferOffset);
    // Deserialize message field [pos]
    data.pos = Point2d.deserialize(buffer, bufferOffset);
    // Deserialize message field [heading]
    data.heading = Angle.deserialize(buffer, bufferOffset);
    // Deserialize message field [vrot]
    data.vrot = _deserializer.float32(buffer, bufferOffset);
    // Deserialize message field [vtrans]
    data.vtrans = Point2d.deserialize(buffer, bufferOffset);
    // Deserialize message field [iskick]
    data.iskick = _deserializer.bool(buffer, bufferOffset);
    // Deserialize message field [isvalid]
    data.isvalid = _deserializer.bool(buffer, bufferOffset);
    // Deserialize message field [isstuck]
    data.isstuck = _deserializer.bool(buffer, bufferOffset);
    // Deserialize message field [isdribble]
    data.isdribble = _deserializer.bool(buffer, bufferOffset);
    // Deserialize message field [current_role]
    data.current_role = _deserializer.char(buffer, bufferOffset);
    // Deserialize message field [role_time]
    data.role_time = _deserializer.float32(buffer, bufferOffset);
    // Deserialize message field [target]
    data.target = Point2d.deserialize(buffer, bufferOffset);
    return data;
  }

  static getMessageSize(object) {
    let length = 0;
    length += std_msgs.msg.Header.getMessageSize(object.header);
    return length + 45;
  }

  static datatype() {
    // Returns string type for a message object
    return 'nubot_common/RobotInfo';
  }

  static md5sum() {
    //Returns md5sum for a message object
    return 'a028ed4c7ddb1dc95486b7c6059da8ad';
  }

  static messageDefinition() {
    // Returns full string definition for message
    return `
    Header header
    int32    AgentID
    Point2d  pos
    Angle    heading
    float32  vrot
    Point2d  vtrans
    bool     iskick     
    bool     isvalid 
    bool     isstuck 
    bool     isdribble
    char     current_role
    float32  role_time
    Point2d  target
     
    
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
    MSG: nubot_common/Angle
    float32 theta
    
    `;
  }

  static Resolve(msg) {
    // deep-construct a valid message object instance of whatever was passed in
    if (typeof msg !== 'object' || msg === null) {
      msg = {};
    }
    const resolved = new RobotInfo(null);
    if (msg.header !== undefined) {
      resolved.header = std_msgs.msg.Header.Resolve(msg.header)
    }
    else {
      resolved.header = new std_msgs.msg.Header()
    }

    if (msg.AgentID !== undefined) {
      resolved.AgentID = msg.AgentID;
    }
    else {
      resolved.AgentID = 0
    }

    if (msg.pos !== undefined) {
      resolved.pos = Point2d.Resolve(msg.pos)
    }
    else {
      resolved.pos = new Point2d()
    }

    if (msg.heading !== undefined) {
      resolved.heading = Angle.Resolve(msg.heading)
    }
    else {
      resolved.heading = new Angle()
    }

    if (msg.vrot !== undefined) {
      resolved.vrot = msg.vrot;
    }
    else {
      resolved.vrot = 0.0
    }

    if (msg.vtrans !== undefined) {
      resolved.vtrans = Point2d.Resolve(msg.vtrans)
    }
    else {
      resolved.vtrans = new Point2d()
    }

    if (msg.iskick !== undefined) {
      resolved.iskick = msg.iskick;
    }
    else {
      resolved.iskick = false
    }

    if (msg.isvalid !== undefined) {
      resolved.isvalid = msg.isvalid;
    }
    else {
      resolved.isvalid = false
    }

    if (msg.isstuck !== undefined) {
      resolved.isstuck = msg.isstuck;
    }
    else {
      resolved.isstuck = false
    }

    if (msg.isdribble !== undefined) {
      resolved.isdribble = msg.isdribble;
    }
    else {
      resolved.isdribble = false
    }

    if (msg.current_role !== undefined) {
      resolved.current_role = msg.current_role;
    }
    else {
      resolved.current_role = 0
    }

    if (msg.role_time !== undefined) {
      resolved.role_time = msg.role_time;
    }
    else {
      resolved.role_time = 0.0
    }

    if (msg.target !== undefined) {
      resolved.target = Point2d.Resolve(msg.target)
    }
    else {
      resolved.target = new Point2d()
    }

    return resolved;
    }
};

module.exports = RobotInfo;
