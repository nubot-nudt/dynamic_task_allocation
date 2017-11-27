; Auto-generated. Do not edit!


(cl:in-package nubot_common-msg)


;//! \htmlinclude TargetInfo.msg.html

(cl:defclass <TargetInfo> (roslisp-msg-protocol:ros-message)
  ((header
    :reader header
    :initarg :header
    :type std_msgs-msg:Header
    :initform (cl:make-instance 'std_msgs-msg:Header))
   (target
    :reader target
    :initarg :target
    :type (cl:vector nubot_common-msg:Point2d)
   :initform (cl:make-array 0 :element-type 'nubot_common-msg:Point2d :initial-element (cl:make-instance 'nubot_common-msg:Point2d))))
)

(cl:defclass TargetInfo (<TargetInfo>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <TargetInfo>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'TargetInfo)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name nubot_common-msg:<TargetInfo> is deprecated: use nubot_common-msg:TargetInfo instead.")))

(cl:ensure-generic-function 'header-val :lambda-list '(m))
(cl:defmethod header-val ((m <TargetInfo>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader nubot_common-msg:header-val is deprecated.  Use nubot_common-msg:header instead.")
  (header m))

(cl:ensure-generic-function 'target-val :lambda-list '(m))
(cl:defmethod target-val ((m <TargetInfo>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader nubot_common-msg:target-val is deprecated.  Use nubot_common-msg:target instead.")
  (target m))
(cl:defmethod roslisp-msg-protocol:serialize ((msg <TargetInfo>) ostream)
  "Serializes a message object of type '<TargetInfo>"
  (roslisp-msg-protocol:serialize (cl:slot-value msg 'header) ostream)
  (cl:let ((__ros_arr_len (cl:length (cl:slot-value msg 'target))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) __ros_arr_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) __ros_arr_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) __ros_arr_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) __ros_arr_len) ostream))
  (cl:map cl:nil #'(cl:lambda (ele) (roslisp-msg-protocol:serialize ele ostream))
   (cl:slot-value msg 'target))
)
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <TargetInfo>) istream)
  "Deserializes a message object of type '<TargetInfo>"
  (roslisp-msg-protocol:deserialize (cl:slot-value msg 'header) istream)
  (cl:let ((__ros_arr_len 0))
    (cl:setf (cl:ldb (cl:byte 8 0) __ros_arr_len) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 8) __ros_arr_len) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 16) __ros_arr_len) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 24) __ros_arr_len) (cl:read-byte istream))
  (cl:setf (cl:slot-value msg 'target) (cl:make-array __ros_arr_len))
  (cl:let ((vals (cl:slot-value msg 'target)))
    (cl:dotimes (i __ros_arr_len)
    (cl:setf (cl:aref vals i) (cl:make-instance 'nubot_common-msg:Point2d))
  (roslisp-msg-protocol:deserialize (cl:aref vals i) istream))))
  msg
)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<TargetInfo>)))
  "Returns string type for a message object of type '<TargetInfo>"
  "nubot_common/TargetInfo")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'TargetInfo)))
  "Returns string type for a message object of type 'TargetInfo"
  "nubot_common/TargetInfo")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<TargetInfo>)))
  "Returns md5sum for a message object of type '<TargetInfo>"
  "a4938944832bdc9277041fe2fa758dce")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'TargetInfo)))
  "Returns md5sum for a message object of type 'TargetInfo"
  "a4938944832bdc9277041fe2fa758dce")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<TargetInfo>)))
  "Returns full string definition for message of type '<TargetInfo>"
  (cl:format cl:nil "Header header~%Point2d[] target~%~%================================================================================~%MSG: std_msgs/Header~%# Standard metadata for higher-level stamped data types.~%# This is generally used to communicate timestamped data ~%# in a particular coordinate frame.~%# ~%# sequence ID: consecutively increasing ID ~%uint32 seq~%#Two-integer timestamp that is expressed as:~%# * stamp.sec: seconds (stamp_secs) since epoch (in Python the variable is called 'secs')~%# * stamp.nsec: nanoseconds since stamp_secs (in Python the variable is called 'nsecs')~%# time-handling sugar is provided by the client library~%time stamp~%#Frame this data is associated with~%# 0: no frame~%# 1: global frame~%string frame_id~%~%================================================================================~%MSG: nubot_common/Point2d~%float32 x~%float32 y~%~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'TargetInfo)))
  "Returns full string definition for message of type 'TargetInfo"
  (cl:format cl:nil "Header header~%Point2d[] target~%~%================================================================================~%MSG: std_msgs/Header~%# Standard metadata for higher-level stamped data types.~%# This is generally used to communicate timestamped data ~%# in a particular coordinate frame.~%# ~%# sequence ID: consecutively increasing ID ~%uint32 seq~%#Two-integer timestamp that is expressed as:~%# * stamp.sec: seconds (stamp_secs) since epoch (in Python the variable is called 'secs')~%# * stamp.nsec: nanoseconds since stamp_secs (in Python the variable is called 'nsecs')~%# time-handling sugar is provided by the client library~%time stamp~%#Frame this data is associated with~%# 0: no frame~%# 1: global frame~%string frame_id~%~%================================================================================~%MSG: nubot_common/Point2d~%float32 x~%float32 y~%~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <TargetInfo>))
  (cl:+ 0
     (roslisp-msg-protocol:serialization-length (cl:slot-value msg 'header))
     4 (cl:reduce #'cl:+ (cl:slot-value msg 'target) :key #'(cl:lambda (ele) (cl:declare (cl:ignorable ele)) (cl:+ (roslisp-msg-protocol:serialization-length ele))))
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <TargetInfo>))
  "Converts a ROS message object to a list"
  (cl:list 'TargetInfo
    (cl:cons ':header (header msg))
    (cl:cons ':target (target msg))
))
