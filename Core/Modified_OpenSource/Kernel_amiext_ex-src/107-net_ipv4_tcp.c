--- linux_org/net/ipv4/tcp.c	2019-01-22 18:46:47.286520446 +0800
+++ linux/net/ipv4/tcp.c	2019-01-22 18:47:22.972645294 +0800
@@ -765,6 +765,12 @@
 				ret = -EAGAIN;
 				break;
 			}
+			/* if __tcp_splice_read() got nothing while we have
+			 * an skb in receive queue, we do not want to loop.
+			 * This might happen with URG data.
+			 */
+			if (!skb_queue_empty(&sk->sk_receive_queue))
+				break;			
 			sk_wait_data(sk, &timeo);
 			if (signal_pending(current)) {
 				ret = sock_intr_errno(timeo);