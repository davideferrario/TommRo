
#ifndef TOMMROC_CRYPTO_SSL_H_
#define TOMMROC_CRYPTO_SSL_H_

/*
 *******************************************************************************
 * License
 * (C) Copyright 2017
 *******************************************************************************
 *
 * Permission is granted to anyone to use this software for any purpose,
 * including commercial applications according to the supply agreement.
 *
 * 1. The origin of this software must not be misrepresented; you must not
 *    claim that you wrote the original software.
 * 2. This notice may not be removed or altered from any source distribution.
 *
 * DISCLAIMER OF WARRANTY/LIMITATION OF REMEDIES: this software is provided
 * "AS IS", with no express or implied warranties of any kind, including,
 * but not limited to, any implied warranties of merchantability or
 * fitness for any particular purpose or warranties against infringement
 * of any proprietary rights of a third party.
 *
 * Supplier will not be liable for any consequential, incidental, or
 * special damages, or any other relief, or for any claim by any third party,
 * arising from your use of this Software.
 *
 */

/**
 * @defgroup tommRoCCryptoSSL tommRoCCryptoSSL
 *
 * @brief  TommRoC library crypto SSL module
 * @author TommRo Software Department
 *
 * This module is providing hardware abstracted crypto SSL functionality.
 *
 * @{
 */

/*******************************************************************************
 * includes
 ******************************************************************************/
#include "tommRoCErr.h"

#include <stdbool.h>
#include <stdint.h>

/*******************************************************************************
 * defines
 ******************************************************************************/

#define TOMMROC_CRYPTO_SSL_X509_CERT_SUCCESS            (0x00000000)    // The certificate verify has been success.

#define TOMMROC_CRYPTO_SSL_X509_BADCERT_EXPIRED         (0x00000001)    // The certificate validity has expired.
#define TOMMROC_CRYPTO_SSL_X509_BADCERT_REVOKED         (0x00000002)    // The certificate has been revoked (is on a CRL).
#define TOMMROC_CRYPTO_SSL_X509_BADCERT_CN_MISMATCH     (0x00000004)    // The certificate Common Name (CN) does not match with the expected CN.
#define TOMMROC_CRYPTO_SSL_X509_BADCERT_NOT_TRUSTED     (0x00000008)    // The certificate is not correctly signed by the trusted CA.
#define TOMMROC_CRYPTO_SSL_X509_BADCRL_NOT_TRUSTED      (0x00000010)    // The CRL is not correctly signed by the trusted CA.
#define TOMMROC_CRYPTO_SSL_X509_BADCRL_EXPIRED          (0x00000020)    // The CRL is expired.
#define TOMMROC_CRYPTO_SSL_X509_BADCERT_MISSING         (0x00000040)    // Certificate was missing.
#define TOMMROC_CRYPTO_SSL_X509_BADCERT_SKIP_VERIFY     (0x00000080)    // Certificate verification was skipped.
#define TOMMROC_CRYPTO_SSL_X509_BADCERT_OTHER           (0x00000100)    // Other reason (can be used by verify callback)
#define TOMMROC_CRYPTO_SSL_X509_BADCERT_FUTURE          (0x00000200)    // The certificate validity starts in the future.
#define TOMMROC_CRYPTO_SSL_X509_BADCRL_FUTURE           (0x00000400)    // The CRL is from the future
#define TOMMROC_CRYPTO_SSL_X509_BADCERT_KEY_USAGE       (0x00000800)    // Usage does not match the keyUsage extension.
#define TOMMROC_CRYPTO_SSL_X509_BADCERT_EXT_KEY_USAGE   (0x00001000)    // Usage does not match the extendedKeyUsage extension.
#define TOMMROC_CRYPTO_SSL_X509_BADCERT_NS_CERT_TYPE    (0x00002000)    // Usage does not match the nsCertType extension.
#define TOMMROC_CRYPTO_SSL_X509_BADCERT_BAD_MD          (0x00004000)    // The certificate is signed with an unacceptable hash.
#define TOMMROC_CRYPTO_SSL_X509_BADCERT_BAD_PK          (0x00008000)    // The certificate is signed with an unacceptable PK alg (eg RSA vs ECDSA).
#define TOMMROC_CRYPTO_SSL_X509_BADCERT_BAD_KEY         (0x00010000)    // The certificate is signed with an unacceptable key (eg bad curve, RSA too short).
#define TOMMROC_CRYPTO_SSL_X509_BADCRL_BAD_MD           (0x00020000)    // The CRL is signed with an unacceptable hash.
#define TOMMROC_CRYPTO_SSL_X509_BADCRL_BAD_PK           (0x00040000)    // The CRL is signed with an unacceptable PK alg (eg RSA vs ECDSA).
#define TOMMROC_CRYPTO_SSL_X509_BADCRL_BAD_KEY          (0x00080000)    // The CRL is signed with an unacceptable key (eg bad curve, RSA too short).

/*******************************************************************************
 * typedefs
 ******************************************************************************/

typedef enum {

    TOMMROC_CRYPTO_SSL_AUTH_MODE_VERIFY_NONE = 0,   // Don't verify certificate
    TOMMROC_CRYPTO_SSL_AUTH_MODE_VERIFY_OPTIONAL,   // Verify certificate - optional
    TOMMROC_CRYPTO_SSL_AUTH_MODE_VERIFY_REQUIRED,   // Verify certificate - required

} tommRoC_crypto_ssl_auth_mode_enum_t;


// tommRoC SSL callback functions type definition.
typedef tommRoC_err_enum_t (*tommRoC_crypto_ssl_init_handshake_host_funct_t)(
                void*                               const   sslCtxPtr,
        const   void*                               const   caChainDataPtr,
        const   uint32_t                                    caChainDataSize,
        const   void*                               const   clientCertDataPtr,
        const   uint32_t                                    clientCertDataSize,
        const   void*                               const   clientPrivKeyDataPtr,
        const   uint32_t                                    clientPrivKeyDataSize,
        const   tommRoC_crypto_ssl_auth_mode_enum_t         sslAuthMode,
        const   char*                               const   hostStrPtr,
        const   uint16_t                                    tcpPort,
                int32_t*                            const   caChainVerifyResPtr);

/**
 * Write application data.
 *
 * return tommRoC_err_enum_t
 *          TOMMRO_C_ERR_SUCCESS    -> write data completed with success. Check amount of data written size [byte] variable.
 *          TOMMRO_C_TIMEOUT_ERR    -> write data failed because of timeout. Amount of data written size [byte] variable MUST be 0.
 *          others                  -> write data failed because of other error. Amount of data written size [byte] MUST be negative.
 */
typedef tommRoC_err_enum_t (*tommRoC_crypto_ssl_write_funct_t)(
                void*                               const   sslCtxPtr,
        const   void*                               const   writeBufferPtr,
        const   uint32_t                                    writeBufferLen,
                int32_t*                            const   writtenLenPtr,
        const   uint32_t                                    writeTimeoutMsec);

/**
 * Read application data.
 *
 * return tommRoC_err_enum_t
 *          TOMMRO_C_ERR_SUCCESS    -> read data completed with success. Check amount of data written size [byte] variable.
 *          TOMMRO_C_TIMEOUT_ERR    -> read data failed because of timeout. Amount of data written size [byte] variable MUST be 0.
 *          others                  -> read data failed because of other error. Amount of data written size [byte] MUST be negative.
 */
typedef tommRoC_err_enum_t (*tommRoC_crypto_ssl_read_funct_t)(
                void*                               const   sslCtxPtr,
                void*                               const   readBufferPtr,
        const   uint32_t                                    readBufferLen,
                int32_t*                            const   readLenPtr,
        const   uint32_t                                    readTimeoutMsec);

typedef tommRoC_err_enum_t (*tommRoC_crypto_close_notify_free_funct_t)(
                void*                               const   sslCtxPtr);

// tommRoC SSL init structure.
typedef struct {

    tommRoC_crypto_ssl_init_handshake_host_funct_t  initHandshakeHostFunct;
    tommRoC_crypto_ssl_write_funct_t                writeFunct;
    tommRoC_crypto_ssl_read_funct_t                 readFunct;
    tommRoC_crypto_close_notify_free_funct_t        closeNotifyFreeFunct;

} tommRoC_crypto_ssl_environment_config_t;

/*******************************************************************************
 * functions
 ******************************************************************************/


/******************* SSL environment init/close functs */

/**
 * SSL environment init.
 *
 * param[in]        initConfigPtr           SSL environment configuration.
 *
 * return tommRoC_err_enum_t
 */
tommRoC_err_enum_t tommRoCCryptoSSLInitEnv(const tommRoC_crypto_ssl_environment_config_t* const initConfigPtr);

/**
 * SSL environment close.
 *
 * return tommRoC_err_enum_t
 */
tommRoC_err_enum_t tommRoCCryptoSSLCloseEnv(void);

/**
 * Check if library SSL environment is init.
 *
 * param[in]        isInitPtr               Is init boolean status.
 *
 * return tommRoC_hw_err_enum_t
 */
tommRoC_err_enum_t tommRoCCryptoSSLIsInitEnv(bool* const isInitPtr);


/******************* SSL environment functs */

/**
 * Initialize/Start an SSL context/session and make handshake with the specified host.
 *
 * param[in/out]    sslCtxPtr               SSL opaque context pointer.
 * param[in]        caChainDataPtr          CA chain certificate (PEM or DER format) data buffer pointer (NULL if none).
 * param[in]        caChainDataSize         CA chain certificate (including the terminating character) size [byte] (0 if none).
 * param[in]        clientCertDataPtr       client certificate (PEM or DER format) data buffer pointer (NULL if none).
 * param[in]        clientCertDataSize      client certificate (including the terminating character) size [byte] (0 if none).
 * param[in]        clientPrivKeyDataPtr    client private key (PEM or DER format) data buffer pointer (NULL if none)..
 * param[in]        clientPrivKeyDataSize   client private key (including the terminating character) size [byte] (0 if none).
 * param[in]        sslAuthMode             certificate verify mode.
 * param[in]        hostStrPtr              host address as string to connect pointer.
 *                                          NOTE: if host address is ipV4 format (xxx.xxx.xxx.xxx), it will be used as IP address.
 * param[in]        tcpPort                 TCP port to connect.
 * param[out]       caChainVerifyResPtr     low level result of the CA chain certificate verification pointer.
 *                                          0   -> certificate verification success.
 *                                          -1  -> result is not available. (e.g. the handshake aborts early).
 *                                          A bitwise combination of TOMMROC_CRYPTO_SSL_X509_BADCERT and TOMMROC_CRYPTO_SSL_X509_BADCRL failure flags.
 *
 * return tommRoC_err_enum_t
 */
tommRoC_err_enum_t tommRoCCryptoSSLInitHandshakeHost(
                void*                               const   sslCtxPtr,
        const   void*                               const   caChainDataPtr,
        const   uint32_t                                    caChainDataSize,
        const   void*                               const   clientCertDataPtr,
        const   uint32_t                                    clientCertDataSize,
        const   void*                               const   clientPrivKeyDataPtr,
        const   uint32_t                                    clientPrivKeyDataSize,
        const   tommRoC_crypto_ssl_auth_mode_enum_t         sslAuthMode,
        const   char*                               const   hostStrPtr,
        const   uint16_t                                    tcpPort,
                int32_t*                            const   caChainVerifyResPtr);

/**
 * Write application data.
 *
 * param[in/out]    sslCtxPtr               SSL opaque context pointer.
 * param[in]        writeBufferPtr          application data buffer pointer.
 * param[in]        writeBufferLen          application data buffer to write size [byte].
 * param[out]       writtenLenPtr           amount of application data written size [byte]. Set to negative value if error occur.
 * param[in]        writeTimeoutMsec        timeout of write operation [msec].
 *
 * return tommRoC_err_enum_t
 *          TOMMRO_C_ERR_SUCCESS    -> write data completed with success. Check amount of data written size [byte] variable.
 *          TOMMRO_C_TIMEOUT_ERR    -> write data failed because of timeout. Amount of data written size [byte] variable MUST be 0.
 *          others                  -> write data failed because of other error. Amount of data written size [byte] MUST be negative.
 */
tommRoC_err_enum_t tommRoCCryptoSSLWrite(
                void*                               const   sslCtxPtr,
        const   void*                               const   writeBufferPtr,
        const   uint32_t                                    writeBufferLen,
                int32_t*                            const   writtenLenPtr,
        const   uint32_t                                    writeTimeoutMsec);

/**
 * Read application data.
 *
 * param[in/out]    sslCtxPtr               SSL opaque context pointer.
 * param[out]       readBufferPtr           output data buffer pointer.
 * param[in]        readBufferLen           data buffer to read size [byte].
 * param[out]       readLenPtr              amount of data read size [byte]. Set to negative value if error occur.
 * param[in]        readTimeoutMsec         timeout of read operation [msec].
 *
 * return tommRoC_err_enum_t
 *          TOMMRO_C_ERR_SUCCESS    -> read data completed with success. Check amount of data written size [byte] variable.
 *          TOMMRO_C_TIMEOUT_ERR    -> read data failed because of timeout. Amount of data written size [byte] variable MUST be 0.
 *          others                  -> read data failed because of other error. Amount of data written size [byte] MUST be negative.
 */
tommRoC_err_enum_t tommRoCCryptoSSLRead(
                void*                               const   sslCtxPtr,
                void*                               const   readBufferPtr,
        const   uint32_t                                    readBufferLen,
                int32_t*                            const   readLenPtr,
        const   uint32_t                                    readTimeoutMsec);

/**
 * Notify the peer that the connection is being closed and free SSL context.
 *
 * param[in/out]    sslCtxPtr               SSL opaque context pointer.
 *
 * return tommRoC_err_enum_t
 */
tommRoC_err_enum_t tommRoCCryptoSSLCloseNotifyFree(
                void*                               const   sslCtxPtr);

/**
 * @}
 */

#endif
