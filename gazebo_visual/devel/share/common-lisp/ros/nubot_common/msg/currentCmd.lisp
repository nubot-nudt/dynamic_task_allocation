; Auto-generated. Do not edit!


(cl:in-package nubot_common-msg)


;//! \htmlinclude currentCmd.msg.html

(cl:defclass <currentCmd> (roslisp-msg-protocol:ros-message)
  ((current
    :reader current
    :initarg :current
    :type cl:integer
    :initform 0))
)

(cl:defclass currentCmd (<currentCmd>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <currentCmd>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'currentCmd)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name nubot_common-msg:<currentCmd> is deprecated: use nubot_common-msg:currentCmd instead.")))

(cl:ensure-generic-function 'current-val :lambda-list '(m))
(cl:defmethod current-val ((m <currentCmd>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader nubot_common-msg:current-val is deprecated.  Use nubot_common-msg:current instead.")
  (current m))
(cl:defmethod roslisp-msg-protocol:serialize ((msg <currentCmd>) ostream)
  "Serializes a message object of type '<currentCmd>"
  (cl:let* ((signed (cl:slot-value msg 'current)) (unsigned (cl:if (cl:< signed 0) (cl:+ signed 4294967296) signed)))
    (cl:write-byte (cl:ldb (cl:byte 8 0) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) unsigned) ostream)
    )
)
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <currentCmd>) istream)
  "Deserializes a message object of type '<currentCmd>"
    (cl:let ((unsigned 0))
      (cl:setf (cl:ldb (cl:byte 8 0) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) unsigned) (cl:read-byte istream))
      (cl:setf (cl:slot-value msg 'current) (cl:if (cl:< unsigned 2147483648) unsigned (cl:- unsigned 4294967296))))
  msg
)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<currentCmd>)))
  "Returns string type for a message object of type '<currentCmd>"
  "nubot_common/currentCmd")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'currentCmd)))
  "Returns string type for a message object of type 'currentCmd"
  "nubot_common/currentCmd")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<currentCmd>)))
  "Returns md5sum for a message object of type '<currentCmd>"
  "034ddbc97d77dfabd91aa8abddfb4453")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'currentCmd)))
  "Returns md5sum for a message object of type 'currentCmd"
  "034ddbc97d77dfabd91aa8abddfb4453")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<currentCmd>)))
  "Returns full string definition for message of type '<currentCmd>"
  (cl:format cl:nil "int32 current~%~%~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'currentCmd)))
  "Returns full string definition for message of type 'currentCmd"
  (cl:format cl:nil "int32 current~%~%~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <currentCmd>))
  (cl:+ 0
     4
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <currentCmd>))
  "Converts a ROS message object to a list"
  (cl:list 'currentCmd
    (cl:cons ':current (current msg))
))
