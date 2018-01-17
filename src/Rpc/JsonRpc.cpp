// Copyright © 2011-2016 The Cryptonote developers
// All Rights Reversed ® GGTM.eu Underground Services
// Distributed under the MIT/X11 software license,
// see http://www.opensource.org/licenses/mit-license.php.

#include "JsonRpc.h"
#include "Rpc/HttpClient.h"

namespace CryptoNote {

namespace JsonRpc {

JsonRpcError::JsonRpcError() : code(0) {}

JsonRpcError::JsonRpcError(int c) : code(c) {
  switch (c) {
  case errParseError: message = "Parse failed"; break;
  case errInvalidRequest: message = "Invalid request"; break;
  case errMethodNotFound: message = "Method not found"; break;
  case errInvalidParams: message = "Invalid params"; break;
  case errInternalError: message = "Internal error"; break;
  default: message = "Something broke"; break;
  }
}

JsonRpcError::JsonRpcError(int c, const std::string& msg) : code(c), message(msg) {
}

void invokeJsonRpcCommand(HttpClient& httpClient, JsonRpcRequest& jsReq, JsonRpcResponse& jsRes) {
  HttpRequest httpReq;
  HttpResponse httpRes;

  httpReq.setUrl("/json_rpc");
  httpReq.setBody(jsReq.getBody());

  httpClient.request(httpReq, httpRes);

  if (httpRes.getStatus() != HttpResponse::STATUS_200) {
    throw std::runtime_error("JSON-RPC call failed, HTTP said: " + std::to_string(httpRes.getStatus()));
  }

  jsRes.parse(httpRes.getBody());

  JsonRpcError err;
  if (jsRes.getError(err)) {
    throw err;
  }
}


}
}
