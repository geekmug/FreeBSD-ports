--- third_party/webrtc/base/physicalsocketserver.cc.orig	2017-01-26 00:50:17 UTC
+++ third_party/webrtc/base/physicalsocketserver.cc
@@ -61,7 +61,11 @@ typedef void* SockOptArg;
 
 int64_t GetSocketRecvTimestamp(int socket) {
   struct timeval tv_ioctl;
+#if defined(WEBRTC_BSD)
+  int ret = ioctl(socket, SO_TIMESTAMP, &tv_ioctl);
+#else
   int ret = ioctl(socket, SIOCGSTAMP, &tv_ioctl);
+#endif
   if (ret != 0)
     return -1;
   int64_t timestamp =
@@ -274,7 +278,7 @@ int PhysicalSocket::GetOption(Option opt
   socklen_t optlen = sizeof(*value);
   int ret = ::getsockopt(s_, slevel, sopt, (SockOptArg)value, &optlen);
   if (ret != -1 && opt == OPT_DONTFRAGMENT) {
-#if defined(WEBRTC_LINUX) && !defined(WEBRTC_ANDROID)
+#if defined(WEBRTC_LINUX) && !defined(WEBRTC_ANDROID) && !defined(WEBRTC_BSD)
     *value = (*value != IP_PMTUDISC_DONT) ? 1 : 0;
 #endif
   }
@@ -287,7 +291,7 @@ int PhysicalSocket::SetOption(Option opt
   if (TranslateOption(opt, &slevel, &sopt) == -1)
     return -1;
   if (opt == OPT_DONTFRAGMENT) {
-#if defined(WEBRTC_LINUX) && !defined(WEBRTC_ANDROID)
+#if defined(WEBRTC_LINUX) && !defined(WEBRTC_ANDROID) && !defined(WEBRTC_BSD)
     value = (value) ? IP_PMTUDISC_DO : IP_PMTUDISC_DONT;
 #endif
   }
@@ -569,10 +573,10 @@ int PhysicalSocket::TranslateOption(Opti
       *slevel = IPPROTO_IP;
       *sopt = IP_DONTFRAGMENT;
       break;
-#elif defined(WEBRTC_MAC) || defined(BSD) || defined(__native_client__)
+#elif defined(WEBRTC_MAC) || defined(WEBRTC_BSD) || defined(__native_client__)
       LOG(LS_WARNING) << "Socket::OPT_DONTFRAGMENT not supported.";
       return -1;
-#elif defined(WEBRTC_POSIX)
+#elif defined(WEBRTC_POSIX) && !defined(WEBRTC_BSD)
       *slevel = IPPROTO_IP;
       *sopt = IP_MTU_DISCOVER;
       break;
