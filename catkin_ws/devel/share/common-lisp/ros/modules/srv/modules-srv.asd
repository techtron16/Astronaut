
(cl:in-package :asdf)

(defsystem "modules-srv"
  :depends-on (:roslisp-msg-protocol :roslisp-utils :geometry_msgs-msg
               :nav_msgs-msg
               :std_msgs-msg
)
  :components ((:file "_package")
    (:file "recon_req" :depends-on ("_package_recon_req"))
    (:file "_package_recon_req" :depends-on ("_package"))
    (:file "target_req" :depends-on ("_package_target_req"))
    (:file "_package_target_req" :depends-on ("_package"))
  ))