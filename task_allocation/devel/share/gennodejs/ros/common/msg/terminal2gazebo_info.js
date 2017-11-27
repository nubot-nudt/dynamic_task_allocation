// Auto-generated. Do not edit!

// (in-package common.msg)


"use strict";

const _serializer = _ros_msg_utils.Serialize;
const _arraySerializer = _serializer.Array;
const _deserializer = _ros_msg_utils.Deserialize;
const _arrayDeserializer = _deserializer.Array;
const _finder = _ros_msg_utils.Find;
const _getByteLength = _ros_msg_utils.getByteLength;

//-----------------------------------------------------------

class terminal2gazebo_info {
  constructor(initObj={}) {
    if (initObj === null) {
      // initObj === null is a special case for deserialization where we don't initialize fields
      this.map_height_msg = null;
      this.map_width_msg = null;
      this.map_room_msg = null;
    }
    else {
      if (initObj.hasOwnProperty('map_height_msg')) {
        this.map_height_msg = initObj.map_height_msg
      }
      else {
        this.map_height_msg = 0;
      }
      if (initObj.hasOwnProperty('map_width_msg')) {
        this.map_width_msg = initObj.map_width_msg
      }
      else {
        this.map_width_msg = 0;
      }
      if (initObj.hasOwnProperty('map_room_msg')) {
        this.map_room_msg = initObj.map_room_msg
      }
      else {
        this.map_room_msg = 0;
      }
    }
  }

  static serialize(obj, buffer, bufferOffset) {
    // Serializes a message object of type terminal2gazebo_info
    // Serialize message field [map_height_msg]
    bufferOffset = _serializer.int16(obj.map_height_msg, buffer, bufferOffset);
    // Serialize message field [map_width_msg]
    bufferOffset = _serializer.int16(obj.map_width_msg, buffer, bufferOffset);
    // Serialize message field [map_room_msg]
    bufferOffset = _serializer.int16(obj.map_room_msg, buffer, bufferOffset);
    return bufferOffset;
  }

  static deserialize(buffer, bufferOffset=[0]) {
    //deserializes a message object of type terminal2gazebo_info
    let len;
    let data = new terminal2gazebo_info(null);
    // Deserialize message field [map_height_msg]
    data.map_height_msg = _deserializer.int16(buffer, bufferOffset);
    // Deserialize message field [map_width_msg]
    data.map_width_msg = _deserializer.int16(buffer, bufferOffset);
    // Deserialize message field [map_room_msg]
    data.map_room_msg = _deserializer.int16(buffer, bufferOffset);
    return data;
  }

  static getMessageSize(object) {
    return 6;
  }

  static datatype() {
    // Returns string type for a message object
    return 'common/terminal2gazebo_info';
  }

  static md5sum() {
    //Returns md5sum for a message object
    return 'f08900b20a86fa5aa1214f8fc88dcbd2';
  }

  static messageDefinition() {
    // Returns full string definition for message
    return `
    int16  map_height_msg                                      
    int16  map_width_msg                                       
    int16  map_room_msg                                         
    
    `;
  }

  static Resolve(msg) {
    // deep-construct a valid message object instance of whatever was passed in
    if (typeof msg !== 'object' || msg === null) {
      msg = {};
    }
    const resolved = new terminal2gazebo_info(null);
    if (msg.map_height_msg !== undefined) {
      resolved.map_height_msg = msg.map_height_msg;
    }
    else {
      resolved.map_height_msg = 0
    }

    if (msg.map_width_msg !== undefined) {
      resolved.map_width_msg = msg.map_width_msg;
    }
    else {
      resolved.map_width_msg = 0
    }

    if (msg.map_room_msg !== undefined) {
      resolved.map_room_msg = msg.map_room_msg;
    }
    else {
      resolved.map_room_msg = 0
    }

    return resolved;
    }
};

module.exports = terminal2gazebo_info;
