; Auto-generated. Do not edit!


(cl:in-package allocation-msg)


;//! \htmlinclude DebugInfo.msg.html

(cl:defclass <DebugInfo> (roslisp-msg-protocol:ros-message)
  ((d1
    :reader d1
    :initarg :d1
    :type cl:float
    :initform 0.0)
   (d2
    :reader d2
    :initarg :d2
    :type cl:float
    :initform 0.0))
)

(cl:defclass DebugInfo (<DebugInfo>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <DebugInfo>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'DebugInfo)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name allocation-msg:<DebugInfo> is deprecated: use allocation-msg:DebugInfo instead.")))

(cl:ensure-generic-function 'd1-val :lambda-list '(m))
(cl:defmethod d1-val ((m <DebugInfo>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader allocation-msg:d1-val is deprecated.  Use allocation-msg:d1 instead.")
  (d1 m))

(cl:ensure-generic-function 'd2-val :lambda-list '(m))
(cl:defmethod d2-val ((m <DebugInfo>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader allocation-msg:d2-val is deprecated.  Use allocation-msg:d2 instead.")
  (d2 m))
(cl:defmethod roslisp-msg-protocol:serialize ((msg <DebugInfo>) ostream)
  "Serializes a message object of type '<DebugInfo>"
  (cl:let ((bits (roslisp-utils:encode-single-float-bits (cl:slot-value msg 'd1))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream))
  (cl:let ((bits (roslisp-utils:encode-single-float-bits (cl:slot-value msg 'd2))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream))
)
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <DebugInfo>) istream)
  "Deserializes a message object of type '<DebugInfo>"
    (cl:let ((bits 0))
      (cl:setf (cl:ldb (cl:byte 8 0) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) bits) (cl:read-byte istream))
    (cl:setf (cl:slot-value msg 'd1) (roslisp-utils:decode-single-float-bits bits)))
    (cl:let ((bits 0))
      (cl:setf (cl:ldb (cl:byte 8 0) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) bits) (cl:read-byte istream))
    (cl:setf (cl:slot-value msg 'd2) (roslisp-utils:decode-single-float-bits bits)))
  msg
)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<DebugInfo>)))
  "Returns string type for a message object of type '<DebugInfo>"
  "allocation/DebugInfo")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'DebugInfo)))
  "Returns string type for a message object of type 'DebugInfo"
  "allocation/DebugInfo")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<DebugInfo>)))
  "Returns md5sum for a message object of type '<DebugInfo>"
  "1c78ad82c247783d0c3aa95ce147b845")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'DebugInfo)))
  "Returns md5sum for a message object of type 'DebugInfo"
  "1c78ad82c247783d0c3aa95ce147b845")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<DebugInfo>)))
  "Returns full string definition for message of type '<DebugInfo>"
  (cl:format cl:nil "float32 d1~%float32 d2~%~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'DebugInfo)))
  "Returns full string definition for message of type 'DebugInfo"
  (cl:format cl:nil "float32 d1~%float32 d2~%~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <DebugInfo>))
  (cl:+ 0
     4
     4
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <DebugInfo>))
  "Converts a ROS message object to a list"
  (cl:list 'DebugInfo
    (cl:cons ':d1 (d1 msg))
    (cl:cons ':d2 (d2 msg))
))
