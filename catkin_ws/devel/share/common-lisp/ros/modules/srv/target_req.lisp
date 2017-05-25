; Auto-generated. Do not edit!


(cl:in-package modules-srv)


;//! \htmlinclude target_req-request.msg.html

(cl:defclass <target_req-request> (roslisp-msg-protocol:ros-message)
  ((request
    :reader request
    :initarg :request
    :type geometry_msgs-msg:Pose
    :initform (cl:make-instance 'geometry_msgs-msg:Pose)))
)

(cl:defclass target_req-request (<target_req-request>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <target_req-request>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'target_req-request)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name modules-srv:<target_req-request> is deprecated: use modules-srv:target_req-request instead.")))

(cl:ensure-generic-function 'request-val :lambda-list '(m))
(cl:defmethod request-val ((m <target_req-request>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader modules-srv:request-val is deprecated.  Use modules-srv:request instead.")
  (request m))
(cl:defmethod roslisp-msg-protocol:serialize ((msg <target_req-request>) ostream)
  "Serializes a message object of type '<target_req-request>"
  (roslisp-msg-protocol:serialize (cl:slot-value msg 'request) ostream)
)
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <target_req-request>) istream)
  "Deserializes a message object of type '<target_req-request>"
  (roslisp-msg-protocol:deserialize (cl:slot-value msg 'request) istream)
  msg
)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<target_req-request>)))
  "Returns string type for a service object of type '<target_req-request>"
  "modules/target_reqRequest")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'target_req-request)))
  "Returns string type for a service object of type 'target_req-request"
  "modules/target_reqRequest")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<target_req-request>)))
  "Returns md5sum for a message object of type '<target_req-request>"
  "ab16145b44c7b4e33fd358e08d9aef29")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'target_req-request)))
  "Returns md5sum for a message object of type 'target_req-request"
  "ab16145b44c7b4e33fd358e08d9aef29")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<target_req-request>)))
  "Returns full string definition for message of type '<target_req-request>"
  (cl:format cl:nil "geometry_msgs/Pose request~%~%================================================================================~%MSG: geometry_msgs/Pose~%# A representation of pose in free space, composed of postion and orientation. ~%Point position~%Quaternion orientation~%~%================================================================================~%MSG: geometry_msgs/Point~%# This contains the position of a point in free space~%float64 x~%float64 y~%float64 z~%~%================================================================================~%MSG: geometry_msgs/Quaternion~%# This represents an orientation in free space in quaternion form.~%~%float64 x~%float64 y~%float64 z~%float64 w~%~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'target_req-request)))
  "Returns full string definition for message of type 'target_req-request"
  (cl:format cl:nil "geometry_msgs/Pose request~%~%================================================================================~%MSG: geometry_msgs/Pose~%# A representation of pose in free space, composed of postion and orientation. ~%Point position~%Quaternion orientation~%~%================================================================================~%MSG: geometry_msgs/Point~%# This contains the position of a point in free space~%float64 x~%float64 y~%float64 z~%~%================================================================================~%MSG: geometry_msgs/Quaternion~%# This represents an orientation in free space in quaternion form.~%~%float64 x~%float64 y~%float64 z~%float64 w~%~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <target_req-request>))
  (cl:+ 0
     (roslisp-msg-protocol:serialization-length (cl:slot-value msg 'request))
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <target_req-request>))
  "Converts a ROS message object to a list"
  (cl:list 'target_req-request
    (cl:cons ':request (request msg))
))
;//! \htmlinclude target_req-response.msg.html

(cl:defclass <target_req-response> (roslisp-msg-protocol:ros-message)
  ((nav_point
    :reader nav_point
    :initarg :nav_point
    :type geometry_msgs-msg:Pose
    :initform (cl:make-instance 'geometry_msgs-msg:Pose))
   (recon_type
    :reader recon_type
    :initarg :recon_type
    :type cl:integer
    :initform 0))
)

(cl:defclass target_req-response (<target_req-response>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <target_req-response>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'target_req-response)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name modules-srv:<target_req-response> is deprecated: use modules-srv:target_req-response instead.")))

(cl:ensure-generic-function 'nav_point-val :lambda-list '(m))
(cl:defmethod nav_point-val ((m <target_req-response>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader modules-srv:nav_point-val is deprecated.  Use modules-srv:nav_point instead.")
  (nav_point m))

(cl:ensure-generic-function 'recon_type-val :lambda-list '(m))
(cl:defmethod recon_type-val ((m <target_req-response>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader modules-srv:recon_type-val is deprecated.  Use modules-srv:recon_type instead.")
  (recon_type m))
(cl:defmethod roslisp-msg-protocol:serialize ((msg <target_req-response>) ostream)
  "Serializes a message object of type '<target_req-response>"
  (roslisp-msg-protocol:serialize (cl:slot-value msg 'nav_point) ostream)
  (cl:let* ((signed (cl:slot-value msg 'recon_type)) (unsigned (cl:if (cl:< signed 0) (cl:+ signed 18446744073709551616) signed)))
    (cl:write-byte (cl:ldb (cl:byte 8 0) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 32) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 40) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 48) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 56) unsigned) ostream)
    )
)
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <target_req-response>) istream)
  "Deserializes a message object of type '<target_req-response>"
  (roslisp-msg-protocol:deserialize (cl:slot-value msg 'nav_point) istream)
    (cl:let ((unsigned 0))
      (cl:setf (cl:ldb (cl:byte 8 0) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 32) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 40) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 48) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 56) unsigned) (cl:read-byte istream))
      (cl:setf (cl:slot-value msg 'recon_type) (cl:if (cl:< unsigned 9223372036854775808) unsigned (cl:- unsigned 18446744073709551616))))
  msg
)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<target_req-response>)))
  "Returns string type for a service object of type '<target_req-response>"
  "modules/target_reqResponse")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'target_req-response)))
  "Returns string type for a service object of type 'target_req-response"
  "modules/target_reqResponse")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<target_req-response>)))
  "Returns md5sum for a message object of type '<target_req-response>"
  "ab16145b44c7b4e33fd358e08d9aef29")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'target_req-response)))
  "Returns md5sum for a message object of type 'target_req-response"
  "ab16145b44c7b4e33fd358e08d9aef29")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<target_req-response>)))
  "Returns full string definition for message of type '<target_req-response>"
  (cl:format cl:nil "geometry_msgs/Pose nav_point~%int64 recon_type~%~%~%================================================================================~%MSG: geometry_msgs/Pose~%# A representation of pose in free space, composed of postion and orientation. ~%Point position~%Quaternion orientation~%~%================================================================================~%MSG: geometry_msgs/Point~%# This contains the position of a point in free space~%float64 x~%float64 y~%float64 z~%~%================================================================================~%MSG: geometry_msgs/Quaternion~%# This represents an orientation in free space in quaternion form.~%~%float64 x~%float64 y~%float64 z~%float64 w~%~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'target_req-response)))
  "Returns full string definition for message of type 'target_req-response"
  (cl:format cl:nil "geometry_msgs/Pose nav_point~%int64 recon_type~%~%~%================================================================================~%MSG: geometry_msgs/Pose~%# A representation of pose in free space, composed of postion and orientation. ~%Point position~%Quaternion orientation~%~%================================================================================~%MSG: geometry_msgs/Point~%# This contains the position of a point in free space~%float64 x~%float64 y~%float64 z~%~%================================================================================~%MSG: geometry_msgs/Quaternion~%# This represents an orientation in free space in quaternion form.~%~%float64 x~%float64 y~%float64 z~%float64 w~%~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <target_req-response>))
  (cl:+ 0
     (roslisp-msg-protocol:serialization-length (cl:slot-value msg 'nav_point))
     8
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <target_req-response>))
  "Converts a ROS message object to a list"
  (cl:list 'target_req-response
    (cl:cons ':nav_point (nav_point msg))
    (cl:cons ':recon_type (recon_type msg))
))
(cl:defmethod roslisp-msg-protocol:service-request-type ((msg (cl:eql 'target_req)))
  'target_req-request)
(cl:defmethod roslisp-msg-protocol:service-response-type ((msg (cl:eql 'target_req)))
  'target_req-response)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'target_req)))
  "Returns string type for a service object of type '<target_req>"
  "modules/target_req")