/**
 * @file   ngx_http_protect_request_module.c
 * @author Tien Nguyen <nguyenvantien2009@gmail.com>
 * @date   19/05/2021
 *
 * @section LICENSE
 *
 * Copyright (C) 2021 by Tien Nguyen, Nguyen Van Tien <nguyenvantien2009@gmail.com>
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 *
 */
#include <ngx_config.h>
#include <ngx_core.h>
#include <ngx_http.h>


// #define HELLO_WORLD "hello world\r\n"

typedef struct {
    ngx_str_t       uri;
} ngx_http_protect_request_conf_t;

typedef struct {
    ngx_uint_t      status;
} ngx_http_protect_request_ctx_t;

static char *ngx_http_protect_request(ngx_conf_t *cf, ngx_command_t *cmd, void *conf);
static ngx_int_t ngx_http_protect_request_handler(ngx_http_request_t *r);

/**
 * This module provided directive `protect_request`.
 *
 */
static ngx_command_t ngx_http_protect_request_commands[] = {

    { ngx_string("protect_request"), /* directive */
      NGX_HTTP_MAIN_CONF|NGX_HTTP_SRV_CONF|NGX_HTTP_LOC_CONF|NGX_CONF_TAKE1, /* location context and takes
                                            no arguments*/
      ngx_http_protect_request, /* configuration setup function */
      NGX_HTTP_LOC_CONF_OFFSET, /* No offset. Only one context is supported. */
      0, /* No offset when storing the module configuration on struct. */
      NULL},

    ngx_null_command /* command termination */
};

/* The hello world string. */
// static u_char ngx_hello_world[] = HELLO_WORLD;

/* The module context. */
static ngx_http_module_t ngx_http_protect_request_module_ctx = {
    NULL, /* preconfiguration */
    NULL, /* postconfiguration */

    NULL, /* create main configuration */
    NULL, /* init main configuration */

    NULL, /* create server configuration */
    NULL, /* merge server configuration */

    NULL, /* create location configuration */
    NULL /* merge location configuration */
};

/* Module definition. */
ngx_module_t ngx_http_protect_request_module = {
    NGX_MODULE_V1,
    &ngx_http_protect_request_module_ctx, /* module context */
    ngx_http_protect_request_commands, /* module directives */
    NGX_HTTP_MODULE, /* module type */
    NULL, /* init master */
    NULL, /* init module */
    NULL, /* init process */
    NULL, /* init thread */
    NULL, /* exit thread */
    NULL, /* exit process */
    NULL, /* exit master */
    NGX_MODULE_V1_PADDING
};

/**
 * Content handler.
 *
 * @param r
 *   Pointer to the request structure. See http_request.h.
 * @return
 *   The status of the response generation.
 */
static ngx_int_t 
ngx_http_protect_request_handler(ngx_http_request_t *r) 
{

    ngx_http_protect_request_conf_t  *arcf;
    ngx_http_protect_request_ctx_t   *ctx;

    arcf = ngx_http_get_module_loc_conf(r, ngx_http_protect_request_module);

    // validate request
    if (arcf->uri.len == 0) {
        return NGX_DECLINED;
    }

    ctx = ngx_http_get_module_ctx(r, ngx_http_protect_request_module);
    

    // add request header
     
    // send request as proxy
    
    // process response
    if (ctx->status >= NGX_HTTP_OK && ctx->status < NGX_HTTP_SPECIAL_RESPONSE) {
        return NGX_OK;
    }
    return NGX_DECLINED;
} /* ngx_http_protect_request_handler */

/**
 * Configuration setup function that installs the content handler.
 *
 * @param cf
 *   Module configuration structure pointer.
 * @param cmd
 *   Module directives structure pointer.
 * @param conf
 *   Module configuration structure pointer.
 * @return string
 *   Status of the configuration setup.
 */
static char *ngx_http_protect_request(ngx_conf_t *cf, ngx_command_t *cmd, void *conf) 
{

    ngx_http_core_loc_conf_t *clcf; /* pointer to core location configuration */

    /* Install the hello world handler. */
    clcf = ngx_http_conf_get_module_loc_conf(cf, ngx_http_core_module);
    clcf->handler = ngx_http_protect_request_handler;

    return NGX_CONF_OK;
} /* ngx_http_hello_world */
