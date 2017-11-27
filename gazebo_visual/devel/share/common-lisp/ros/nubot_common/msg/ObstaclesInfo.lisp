; Auto-generated. Do not edit!


(cl:in-package nubot_common-msg)


;//! \htmlinclude ObstaclesInfo.msg.html

(cl:defclass <ObstaclesInfo> (roslisp-msg-protocol:ros-message)
  ((header
    :reader header
    :initarg :header
    :type std_msgs-msg:Header
    :initform (cl:make-instance 'std_msgs-msg:Header))
   (pos
    :reader pos
    :initarg :pos
    :type (cl:vector nubot_common-msg:Point2d)
   :initform (cl:make-array 0 :element-type 'nubot_common-msg:Point2d :initial-element (cl:make-instance 'nubot_common-msg:Point2d)))
   (polar_pos
    :reader polar_pos
    :initarg :polar_pos
    :type (cl:vector nubot_common-msg:PPoint)
   :initform (cl:make-array 0 :element-type 'nubot_common-msg:PPoint :initial-element (cl:make-instance 'nubot_common-msg:PPoint))))
)

(cl:defclass ObstaclesInfo (<ObstaclesInfo>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <ObstaclesInfo>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'ObstaclesInfo)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name nubot_common-msg:<ObstaclesInfo> is deprecated: use nubot_common-msg:ObstaclesInfo instead.")))

(cl:ensure-generic-function 'header-val :lambda-list '(m))
(cl:defmethod header-val ((m <ObstaclesInfo>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader nubot_common-msg:header-val is deprecated.  Use nubot_common-msg:header instead.")
  (header m))

(cl:ensure-generic-function 'pos-val :lambda-list '(m))
(cl:defmethod pos-val ((m <ObstaclesInfo>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader nubot_common-msg:pos-val is deprecated.  Use nubot_common-msg:pos instead.")
  (pos m))

(cl:ensure-generic-function 'polar_pos-val :lambda-list '(m))
(cl:defmethod polar_pos-val ((m <ObstaclesInfo>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader nubot_common-msg:polar_pos-val is deprecated.  Use nubot_common-msg:polar_pos instead.")
  (polar_pos m))
(cl:defmethod roslisp-msg-protocol:serialize ((msg <ObstaclesInfo>) ostream)
  "Serializes a message object of type '<ObstaclesInfo>"
  (roslisp-msg-protocol:serialize (cl:slot-value msg 'header) ostream)
  (cl:let ((__ros_arr_len (cl:length (cl:slot-value msg 'pos))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) __ros_arr_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) __ros_arr_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) __ros_arr_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) __ros_arr_len) ostream))
  (cl:map cl:nil #'(cl:lambda (ele) (roslisp-msg-protocol:serialize ele ostream))
   (cl:slot-value msg 'pos))
  (cl:let ((__ros_arr_len (cl:length (cl:slot-value msg 'polar_pos))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) __ros_arr_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) __ros_arr_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) __ros_arr_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) __ros_arr_len) ostream))
  (cl:map cl:nil #'(cl:lambda (ele) (roslisp-msg-protocol:serialize ele ostream))
   (cl:slot-value msg 'polar_pos))
)
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <ObstaclesInfo>) istream)
  "Deserializes a message object of type '<ObstaclesInfo>"
  (roslisp-msg-protocol:deserialize (cl:slot-value msg 'header) istream)
  (cl:let ((__ros_arr_len 0))
    (cl:setf (cl:ldb (cl:byte 8 0) __ros_arr_len) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 8) __ros_arr_len) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 16) __ros_arr_len) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 24) __ros_arr_len) (cl:read-byte istream))
  (cl:setf (cl:slot-value msg 'pos) (cl:make-array __ros_arr_len))
  (cl:let ((vals (cl:slot-value msg 'pos)))
    (cl:dotimes (i __ros_arr_len)
    (cl:setf (cl:aref vals i) (cl:make-instance 'nubot_common-msg:Point2d))
  (roslisp-msg-protocol:deserialize (cl:aref vals i) istream))))
  (cl:let ((__ros_arr_len 0))
    (cl:setf (cl:ldb (cl:byte 8 0) __ros_arr_len) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 8) __ros_arr_len) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 16) __ros_arr_len) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 24) __ros_arr_len) (cl:read-byte istream))
  (cl:setf (cl:slot-value msg 'polar_pos) (cl:make-array __ros_arr_len))
  (cl:let ((vals (cl:slot-value msg 'polar_pos)))
    (cl:dotimes (i __ros_arr_len)
    (cl:setf (cl:aref vals i) (cl:make-instance 'nubot_common-msg:PPoint))
  (roslisp-msg-protocol:deserialize (cl:aref vals i) istream))))
  msg
)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<ObstaclesInfo>)))
  "Returns string type for a message object of type '<ObstaclesInfo>"
  "nubot_common/ObstaclesInfo")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'ObstaclesInfo)))
  "Returns string type for a message object of type 'ObstaclesInfo"
  "nubot_common/ObstaclesInfo")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<ObstaclesInfo>)))
  "Returns md5sum for a message object of type '<ObstaclesInfo>"
  "8850a2241dd98578d2d66d842f5946c8")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'ObstaclesInfo)))
  "Returns md5sum for a message object of type 'ObstaclesInfo"
  "8850a2241dd98578d2d66d842f5946c8")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<ObstaclesInfo>)))
  "Returns full string definition for message of type '<ObstaclesInfo>"
  (cl:format cl:nil "Header header~%Point2d[] pos~%PPoint[] polar_pos~%~%~%================================================================================~%MSG: std_msgs/Header~%# Standard metadata for higher-level stamped data types.~%# This is generally used to communicate timestamped data ~%# in a particular coordinate frame.~%# ~%# sequence ID: consecutively increasing ID ~%uint32 seq~%#Two-integer timestamp that is expressed as:~%# * stamp.sec: seconds (stamp_secs) since epoch (in Python the variable is called 'secs')~%# * stamp.nsec: nanoseconds since stamp_secs (in Python the variable is called 'nsecs')~%# time-handling sugar is provided by the client library~%time stamp~%#Frame this data is associated with~%# 0: no frame~%# 1: global frame~%string frame_id~%~%================================================================================~%MSG: nubot_common/Point2d~%float32 x~%float32 y~%~%================================================================================~%MSG: nubot_common/PPoint~%float32 angle~%float32 radius~%~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'ObstaclesInfo)))
  "Returns full string definition for message of type 'ObstaclesInfo"
  (cl:format cl:nil "Header header~%Point2d[] pos~%PPoint[] polar_pos~%~%~%================================================================================~%MSG: std_msgs/Header~%# Standard metadata for higher-level stamped data types.~%# This is generally used to communicate timestamped data ~%# in a particular coordinate frame.~%# ~%# sequence ID: consecutively increasing ID ~%uint32 seq~%#Two-integer timestamp that is expressed as:~%# * stamp.sec: seconds (stamp_secs) since epoch (in Python the variable is called 'secs')~%# * stamp.nsec: nanoseconds since stamp_secs (in Python the variable is called 'nsecs')~%# time-handling sugar is provided by the client library~%time stamp~%#Frame this data is associated with~%# 0: no frame~%# 1: global frame~%string frame_id~%~%================================================================================~%MSG: nubot_common/Point2d~%float32 x~%float32 y~%~%================================================================================~%MSG: nubot_common/PPoint~%float32 angle~%float32 radius~%~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <ObstaclesInfo>))
  (cl:+ 0
     (roslisp-msg-protocol:serialization-length (cl:slot-value msg 'header))
     4 (cl:reduce #'cl:+ (cl:slot-value msg 'pos) :key #'(cl:lambda (ele) (cl:declare (cl:ignorable ele)) (cl:+ (roslisp-msg-protocol:serialization-length ele))))
     4 (cl:reduce #'cl:+ (cl:slot-value msg 'polar_pos) :key #'(cl:lambda (ele) (cl:declare (cl:ignorable ele)) (cl:+ (roslisp-msg-protocol:serialization-length ele))))
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <ObstaclesInfo>))
  "Converts a ROS message object to a list"
  (cl:list 'ObstaclesInfo
    (cl:cons ':header (header msg))
    (cl:cons ':pos (pos msg))
    (cl:cons ':polar_pos (polar_pos msg))
))
