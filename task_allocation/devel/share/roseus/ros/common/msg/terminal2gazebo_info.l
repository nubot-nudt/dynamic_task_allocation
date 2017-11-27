;; Auto-generated. Do not edit!


(when (boundp 'common::terminal2gazebo_info)
  (if (not (find-package "COMMON"))
    (make-package "COMMON"))
  (shadow 'terminal2gazebo_info (find-package "COMMON")))
(unless (find-package "COMMON::TERMINAL2GAZEBO_INFO")
  (make-package "COMMON::TERMINAL2GAZEBO_INFO"))

(in-package "ROS")
;;//! \htmlinclude terminal2gazebo_info.msg.html


(defclass common::terminal2gazebo_info
  :super ros::object
  :slots (_map_height_msg _map_width_msg _map_room_msg ))

(defmethod common::terminal2gazebo_info
  (:init
   (&key
    ((:map_height_msg __map_height_msg) 0)
    ((:map_width_msg __map_width_msg) 0)
    ((:map_room_msg __map_room_msg) 0)
    )
   (send-super :init)
   (setq _map_height_msg (round __map_height_msg))
   (setq _map_width_msg (round __map_width_msg))
   (setq _map_room_msg (round __map_room_msg))
   self)
  (:map_height_msg
   (&optional __map_height_msg)
   (if __map_height_msg (setq _map_height_msg __map_height_msg)) _map_height_msg)
  (:map_width_msg
   (&optional __map_width_msg)
   (if __map_width_msg (setq _map_width_msg __map_width_msg)) _map_width_msg)
  (:map_room_msg
   (&optional __map_room_msg)
   (if __map_room_msg (setq _map_room_msg __map_room_msg)) _map_room_msg)
  (:serialization-length
   ()
   (+
    ;; int16 _map_height_msg
    2
    ;; int16 _map_width_msg
    2
    ;; int16 _map_room_msg
    2
    ))
  (:serialize
   (&optional strm)
   (let ((s (if strm strm
              (make-string-output-stream (send self :serialization-length)))))
     ;; int16 _map_height_msg
       (write-word _map_height_msg s)
     ;; int16 _map_width_msg
       (write-word _map_width_msg s)
     ;; int16 _map_room_msg
       (write-word _map_room_msg s)
     ;;
     (if (null strm) (get-output-stream-string s))))
  (:deserialize
   (buf &optional (ptr- 0))
   ;; int16 _map_height_msg
     (setq _map_height_msg (sys::peek buf ptr- :short)) (incf ptr- 2)
   ;; int16 _map_width_msg
     (setq _map_width_msg (sys::peek buf ptr- :short)) (incf ptr- 2)
   ;; int16 _map_room_msg
     (setq _map_room_msg (sys::peek buf ptr- :short)) (incf ptr- 2)
   ;;
   self)
  )

(setf (get common::terminal2gazebo_info :md5sum-) "f08900b20a86fa5aa1214f8fc88dcbd2")
(setf (get common::terminal2gazebo_info :datatype-) "common/terminal2gazebo_info")
(setf (get common::terminal2gazebo_info :definition-)
      "int16  map_height_msg                                      
int16  map_width_msg                                       
int16  map_room_msg                                         

")



(provide :common/terminal2gazebo_info "f08900b20a86fa5aa1214f8fc88dcbd2")


