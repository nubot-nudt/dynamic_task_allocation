; Auto-generated. Do not edit!


(cl:in-package common-msg)


;//! \htmlinclude terminal2gazebo_info.msg.html

(cl:defclass <terminal2gazebo_info> (roslisp-msg-protocol:ros-message)
  ((map_height_msg
    :reader map_height_msg
    :initarg :map_height_msg
    :type cl:fixnum
    :initform 0)
   (map_width_msg
    :reader map_width_msg
    :initarg :map_width_msg
    :type cl:fixnum
    :initform 0)
   (map_room_msg
    :reader map_room_msg
    :initarg :map_room_msg
    :type cl:fixnum
    :initform 0))
)

(cl:defclass terminal2gazebo_info (<terminal2gazebo_info>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <terminal2gazebo_info>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'terminal2gazebo_info)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name common-msg:<terminal2gazebo_info> is deprecated: use common-msg:terminal2gazebo_info instead.")))

(cl:ensure-generic-function 'map_height_msg-val :lambda-list '(m))
(cl:defmethod map_height_msg-val ((m <terminal2gazebo_info>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader common-msg:map_height_msg-val is deprecated.  Use common-msg:map_height_msg instead.")
  (map_height_msg m))

(cl:ensure-generic-function 'map_width_msg-val :lambda-list '(m))
(cl:defmethod map_width_msg-val ((m <terminal2gazebo_info>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader common-msg:map_width_msg-val is deprecated.  Use common-msg:map_width_msg instead.")
  (map_width_msg m))

(cl:ensure-generic-function 'map_room_msg-val :lambda-list '(m))
(cl:defmethod map_room_msg-val ((m <terminal2gazebo_info>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader common-msg:map_room_msg-val is deprecated.  Use common-msg:map_room_msg instead.")
  (map_room_msg m))
(cl:defmethod roslisp-msg-protocol:serialize ((msg <terminal2gazebo_info>) ostream)
  "Serializes a message object of type '<terminal2gazebo_info>"
  (cl:let* ((signed (cl:slot-value msg 'map_height_msg)) (unsigned (cl:if (cl:< signed 0) (cl:+ signed 65536) signed)))
    (cl:write-byte (cl:ldb (cl:byte 8 0) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) unsigned) ostream)
    )
  (cl:let* ((signed (cl:slot-value msg 'map_width_msg)) (unsigned (cl:if (cl:< signed 0) (cl:+ signed 65536) signed)))
    (cl:write-byte (cl:ldb (cl:byte 8 0) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) unsigned) ostream)
    )
  (cl:let* ((signed (cl:slot-value msg 'map_room_msg)) (unsigned (cl:if (cl:< signed 0) (cl:+ signed 65536) signed)))
    (cl:write-byte (cl:ldb (cl:byte 8 0) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) unsigned) ostream)
    )
)
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <terminal2gazebo_info>) istream)
  "Deserializes a message object of type '<terminal2gazebo_info>"
    (cl:let ((unsigned 0))
      (cl:setf (cl:ldb (cl:byte 8 0) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) unsigned) (cl:read-byte istream))
      (cl:setf (cl:slot-value msg 'map_height_msg) (cl:if (cl:< unsigned 32768) unsigned (cl:- unsigned 65536))))
    (cl:let ((unsigned 0))
      (cl:setf (cl:ldb (cl:byte 8 0) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) unsigned) (cl:read-byte istream))
      (cl:setf (cl:slot-value msg 'map_width_msg) (cl:if (cl:< unsigned 32768) unsigned (cl:- unsigned 65536))))
    (cl:let ((unsigned 0))
      (cl:setf (cl:ldb (cl:byte 8 0) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) unsigned) (cl:read-byte istream))
      (cl:setf (cl:slot-value msg 'map_room_msg) (cl:if (cl:< unsigned 32768) unsigned (cl:- unsigned 65536))))
  msg
)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<terminal2gazebo_info>)))
  "Returns string type for a message object of type '<terminal2gazebo_info>"
  "common/terminal2gazebo_info")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'terminal2gazebo_info)))
  "Returns string type for a message object of type 'terminal2gazebo_info"
  "common/terminal2gazebo_info")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<terminal2gazebo_info>)))
  "Returns md5sum for a message object of type '<terminal2gazebo_info>"
  "f08900b20a86fa5aa1214f8fc88dcbd2")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'terminal2gazebo_info)))
  "Returns md5sum for a message object of type 'terminal2gazebo_info"
  "f08900b20a86fa5aa1214f8fc88dcbd2")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<terminal2gazebo_info>)))
  "Returns full string definition for message of type '<terminal2gazebo_info>"
  (cl:format cl:nil "int16  map_height_msg                                      ~%int16  map_width_msg                                       ~%int16  map_room_msg                                         ~%~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'terminal2gazebo_info)))
  "Returns full string definition for message of type 'terminal2gazebo_info"
  (cl:format cl:nil "int16  map_height_msg                                      ~%int16  map_width_msg                                       ~%int16  map_room_msg                                         ~%~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <terminal2gazebo_info>))
  (cl:+ 0
     2
     2
     2
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <terminal2gazebo_info>))
  "Converts a ROS message object to a list"
  (cl:list 'terminal2gazebo_info
    (cl:cons ':map_height_msg (map_height_msg msg))
    (cl:cons ':map_width_msg (map_width_msg msg))
    (cl:cons ':map_room_msg (map_room_msg msg))
))
