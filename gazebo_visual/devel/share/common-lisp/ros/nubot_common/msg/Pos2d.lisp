; Auto-generated. Do not edit!


(cl:in-package nubot_common-msg)


;//! \htmlinclude Pos2d.msg.html

(cl:defclass <Pos2d> (roslisp-msg-protocol:ros-message)
  ((header
    :reader header
    :initarg :header
    :type std_msgs-msg:Header
    :initform (cl:make-instance 'std_msgs-msg:Header))
   (pos
    :reader pos
    :initarg :pos
    :type nubot_common-msg:Point2d
    :initform (cl:make-instance 'nubot_common-msg:Point2d)))
)

(cl:defclass Pos2d (<Pos2d>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <Pos2d>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'Pos2d)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name nubot_common-msg:<Pos2d> is deprecated: use nubot_common-msg:Pos2d instead.")))

(cl:ensure-generic-function 'header-val :lambda-list '(m))
(cl:defmethod header-val ((m <Pos2d>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader nubot_common-msg:header-val is deprecated.  Use nubot_common-msg:header instead.")
  (header m))

(cl:ensure-generic-function 'pos-val :lambda-list '(m))
(cl:defmethod pos-val ((m <Pos2d>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader nubot_common-msg:pos-val is deprecated.  Use nubot_common-msg:pos instead.")
  (pos m))
(cl:defmethod roslisp-msg-protocol:serialize ((msg <Pos2d>) ostream)
  "Serializes a message object of type '<Pos2d>"
  (roslisp-msg-protocol:serialize (cl:slot-value msg 'header) ostream)
  (roslisp-msg-protocol:serialize (cl:slot-value msg 'pos) ostream)
)
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <Pos2d>) istream)
  "Deserializes a message object of type '<Pos2d>"
  (roslisp-msg-protocol:deserialize (cl:slot-value msg 'header) istream)
  (roslisp-msg-protocol:deserialize (cl:slot-value msg 'pos) istream)
  msg
)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<Pos2d>)))
  "Returns string type for a message object of type '<Pos2d>"
  "nubot_common/Pos2d")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'Pos2d)))
  "Returns string type for a message object of type 'Pos2d"
  "nubot_common/Pos2d")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<Pos2d>)))
  "Returns md5sum for a message object of type '<Pos2d>"
  "eb6867b60acd4552a8fe8e7d015aa528")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'Pos2d)))
  "Returns md5sum for a message object of type 'Pos2d"
  "eb6867b60acd4552a8fe8e7d015aa528")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<Pos2d>)))
  "Returns full string definition for message of type '<Pos2d>"
  (cl:format cl:nil "Header header~%Point2d pos~%~%~%================================================================================~%MSG: std_msgs/Header~%# Standard metadata for higher-level stamped data types.~%# This is generally used to communicate timestamped data ~%# in a particular coordinate frame.~%# ~%# sequence ID: consecutively increasing ID ~%uint32 seq~%#Two-integer timestamp that is expressed as:~%# * stamp.sec: seconds (stamp_secs) since epoch (in Python the variable is called 'secs')~%# * stamp.nsec: nanoseconds since stamp_secs (in Python the variable is called 'nsecs')~%# time-handling sugar is provided by the client library~%time stamp~%#Frame this data is associated with~%# 0: no frame~%# 1: global frame~%string frame_id~%~%================================================================================~%MSG: nubot_common/Point2d~%float32 x~%float32 y~%~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'Pos2d)))
  "Returns full string definition for message of type 'Pos2d"
  (cl:format cl:nil "Header header~%Point2d pos~%~%~%================================================================================~%MSG: std_msgs/Header~%# Standard metadata for higher-level stamped data types.~%# This is generally used to communicate timestamped data ~%# in a particular coordinate frame.~%# ~%# sequence ID: consecutively increasing ID ~%uint32 seq~%#Two-integer timestamp that is expressed as:~%# * stamp.sec: seconds (stamp_secs) since epoch (in Python the variable is called 'secs')~%# * stamp.nsec: nanoseconds since stamp_secs (in Python the variable is called 'nsecs')~%# time-handling sugar is provided by the client library~%time stamp~%#Frame this data is associated with~%# 0: no frame~%# 1: global frame~%string frame_id~%~%================================================================================~%MSG: nubot_common/Point2d~%float32 x~%float32 y~%~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <Pos2d>))
  (cl:+ 0
     (roslisp-msg-protocol:serialization-length (cl:slot-value msg 'header))
     (roslisp-msg-protocol:serialization-length (cl:slot-value msg 'pos))
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <Pos2d>))
  "Converts a ROS message object to a list"
  (cl:list 'Pos2d
    (cl:cons ':header (header msg))
    (cl:cons ':pos (pos msg))
))
