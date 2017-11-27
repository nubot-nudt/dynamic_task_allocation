;; Auto-generated. Do not edit!


(when (boundp 'nubot_common::RobotInfo)
  (if (not (find-package "NUBOT_COMMON"))
    (make-package "NUBOT_COMMON"))
  (shadow 'RobotInfo (find-package "NUBOT_COMMON")))
(unless (find-package "NUBOT_COMMON::ROBOTINFO")
  (make-package "NUBOT_COMMON::ROBOTINFO"))

(in-package "ROS")
;;//! \htmlinclude RobotInfo.msg.html
(if (not (find-package "STD_MSGS"))
  (ros::roseus-add-msgs "std_msgs"))


(defclass nubot_common::RobotInfo
  :super ros::object
  :slots (_header _AgentID _pos _heading _vrot _vtrans _iskick _isvalid _isstuck _isdribble _current_role _role_time _target ))

(defmethod nubot_common::RobotInfo
  (:init
   (&key
    ((:header __header) (instance std_msgs::Header :init))
    ((:AgentID __AgentID) 0)
    ((:pos __pos) (instance nubot_common::Point2d :init))
    ((:heading __heading) (instance nubot_common::Angle :init))
    ((:vrot __vrot) 0.0)
    ((:vtrans __vtrans) (instance nubot_common::Point2d :init))
    ((:iskick __iskick) nil)
    ((:isvalid __isvalid) nil)
    ((:isstuck __isstuck) nil)
    ((:isdribble __isdribble) nil)
    ((:current_role __current_role) 0)
    ((:role_time __role_time) 0.0)
    ((:target __target) (instance nubot_common::Point2d :init))
    )
   (send-super :init)
   (setq _header __header)
   (setq _AgentID (round __AgentID))
   (setq _pos __pos)
   (setq _heading __heading)
   (setq _vrot (float __vrot))
   (setq _vtrans __vtrans)
   (setq _iskick __iskick)
   (setq _isvalid __isvalid)
   (setq _isstuck __isstuck)
   (setq _isdribble __isdribble)
   (setq _current_role (round __current_role))
   (setq _role_time (float __role_time))
   (setq _target __target)
   self)
  (:header
   (&rest __header)
   (if (keywordp (car __header))
       (send* _header __header)
     (progn
       (if __header (setq _header (car __header)))
       _header)))
  (:AgentID
   (&optional __AgentID)
   (if __AgentID (setq _AgentID __AgentID)) _AgentID)
  (:pos
   (&rest __pos)
   (if (keywordp (car __pos))
       (send* _pos __pos)
     (progn
       (if __pos (setq _pos (car __pos)))
       _pos)))
  (:heading
   (&rest __heading)
   (if (keywordp (car __heading))
       (send* _heading __heading)
     (progn
       (if __heading (setq _heading (car __heading)))
       _heading)))
  (:vrot
   (&optional __vrot)
   (if __vrot (setq _vrot __vrot)) _vrot)
  (:vtrans
   (&rest __vtrans)
   (if (keywordp (car __vtrans))
       (send* _vtrans __vtrans)
     (progn
       (if __vtrans (setq _vtrans (car __vtrans)))
       _vtrans)))
  (:iskick
   (&optional __iskick)
   (if __iskick (setq _iskick __iskick)) _iskick)
  (:isvalid
   (&optional __isvalid)
   (if __isvalid (setq _isvalid __isvalid)) _isvalid)
  (:isstuck
   (&optional __isstuck)
   (if __isstuck (setq _isstuck __isstuck)) _isstuck)
  (:isdribble
   (&optional __isdribble)
   (if __isdribble (setq _isdribble __isdribble)) _isdribble)
  (:current_role
   (&optional __current_role)
   (if __current_role (setq _current_role __current_role)) _current_role)
  (:role_time
   (&optional __role_time)
   (if __role_time (setq _role_time __role_time)) _role_time)
  (:target
   (&rest __target)
   (if (keywordp (car __target))
       (send* _target __target)
     (progn
       (if __target (setq _target (car __target)))
       _target)))
  (:serialization-length
   ()
   (+
    ;; std_msgs/Header _header
    (send _header :serialization-length)
    ;; int32 _AgentID
    4
    ;; nubot_common/Point2d _pos
    (send _pos :serialization-length)
    ;; nubot_common/Angle _heading
    (send _heading :serialization-length)
    ;; float32 _vrot
    4
    ;; nubot_common/Point2d _vtrans
    (send _vtrans :serialization-length)
    ;; bool _iskick
    1
    ;; bool _isvalid
    1
    ;; bool _isstuck
    1
    ;; bool _isdribble
    1
    ;; char _current_role
    1
    ;; float32 _role_time
    4
    ;; nubot_common/Point2d _target
    (send _target :serialization-length)
    ))
  (:serialize
   (&optional strm)
   (let ((s (if strm strm
              (make-string-output-stream (send self :serialization-length)))))
     ;; std_msgs/Header _header
       (send _header :serialize s)
     ;; int32 _AgentID
       (write-long _AgentID s)
     ;; nubot_common/Point2d _pos
       (send _pos :serialize s)
     ;; nubot_common/Angle _heading
       (send _heading :serialize s)
     ;; float32 _vrot
       (sys::poke _vrot (send s :buffer) (send s :count) :float) (incf (stream-count s) 4)
     ;; nubot_common/Point2d _vtrans
       (send _vtrans :serialize s)
     ;; bool _iskick
       (if _iskick (write-byte -1 s) (write-byte 0 s))
     ;; bool _isvalid
       (if _isvalid (write-byte -1 s) (write-byte 0 s))
     ;; bool _isstuck
       (if _isstuck (write-byte -1 s) (write-byte 0 s))
     ;; bool _isdribble
       (if _isdribble (write-byte -1 s) (write-byte 0 s))
     ;; char _current_role
       (write-byte _current_role s)
     ;; float32 _role_time
       (sys::poke _role_time (send s :buffer) (send s :count) :float) (incf (stream-count s) 4)
     ;; nubot_common/Point2d _target
       (send _target :serialize s)
     ;;
     (if (null strm) (get-output-stream-string s))))
  (:deserialize
   (buf &optional (ptr- 0))
   ;; std_msgs/Header _header
     (send _header :deserialize buf ptr-) (incf ptr- (send _header :serialization-length))
   ;; int32 _AgentID
     (setq _AgentID (sys::peek buf ptr- :integer)) (incf ptr- 4)
   ;; nubot_common/Point2d _pos
     (send _pos :deserialize buf ptr-) (incf ptr- (send _pos :serialization-length))
   ;; nubot_common/Angle _heading
     (send _heading :deserialize buf ptr-) (incf ptr- (send _heading :serialization-length))
   ;; float32 _vrot
     (setq _vrot (sys::peek buf ptr- :float)) (incf ptr- 4)
   ;; nubot_common/Point2d _vtrans
     (send _vtrans :deserialize buf ptr-) (incf ptr- (send _vtrans :serialization-length))
   ;; bool _iskick
     (setq _iskick (not (= 0 (sys::peek buf ptr- :char)))) (incf ptr- 1)
   ;; bool _isvalid
     (setq _isvalid (not (= 0 (sys::peek buf ptr- :char)))) (incf ptr- 1)
   ;; bool _isstuck
     (setq _isstuck (not (= 0 (sys::peek buf ptr- :char)))) (incf ptr- 1)
   ;; bool _isdribble
     (setq _isdribble (not (= 0 (sys::peek buf ptr- :char)))) (incf ptr- 1)
   ;; char _current_role
     (setq _current_role (sys::peek buf ptr- :char)) (incf ptr- 1)
   ;; float32 _role_time
     (setq _role_time (sys::peek buf ptr- :float)) (incf ptr- 4)
   ;; nubot_common/Point2d _target
     (send _target :deserialize buf ptr-) (incf ptr- (send _target :serialization-length))
   ;;
   self)
  )

(setf (get nubot_common::RobotInfo :md5sum-) "a028ed4c7ddb1dc95486b7c6059da8ad")
(setf (get nubot_common::RobotInfo :datatype-) "nubot_common/RobotInfo")
(setf (get nubot_common::RobotInfo :definition-)
      "Header header
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

")



(provide :nubot_common/RobotInfo "a028ed4c7ddb1dc95486b7c6059da8ad")


