#
# Copyright (c) 2019 Cossack Labs Limited
#
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
#
# http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.
#

JSecrypt_SRC = $(SRC_PATH)/jsecrypt
JSecrypt_OBJ = $(OBJ_PATH)/$(JSecrypt_SRC)

JSecrypt_SOURCES = $(wildcard $(JSecrypt_SRC)/*.cpp)
JSecrypt_HEADERS = $(wildcard $(JSecrypt_SRC)/*.hpp)
#JSecrypt_PACKAGE += $(JSecrypt_SRC)/README.md
#JSecrypt_PACKAGE += $(JSecrypt_SRC)/LICENSE
JSecrypt_PACKAGE += $(JSecrypt_SRC)/package.json

# Unfortunately, clang-tidy requires full compilation flags to be able to work and
# node-gyp add quite a few custom flags with include search paths. It also requires
# some Node modules for compilation. We recreate the same environment here as for
# the "jsecrypt_install" target. However, we can't do that without NPM present.
# Therefore we format Jsecrypt code only if NodeJS is actually installed.
ifdef NPM_VERSION

# A hack to install "nan" before formatting any Jsecrypt files
FMT_FIXUP += $(JSecrypt_OBJ)/node_modules/nan
FMT_CHECK += $(JSecrypt_OBJ)/node_modules/nan

$(JSecrypt_OBJ)/node_modules/nan:
	@mkdir -p $(JSecrypt_OBJ) && cd $(JSecrypt_OBJ) && npm install nan && cd -

FMT_FIXUP += $(patsubst %,$(OBJ_PATH)/%.fmt_fixup, $(JSecrypt_SOURCES) $(JSecrypt_HEADERS))
FMT_CHECK += $(patsubst %,$(OBJ_PATH)/%.fmt_check, $(JSecrypt_SOURCES) $(JSecrypt_HEADERS))

$(JSecrypt_OBJ)/%: CFLAGS += $(JSecrypt_CFLAGS)

JSecrypt_CFLAGS += -I$(JSecrypt_OBJ)/node_modules/nan

ifdef IS_LINUX
JSecrypt_CFLAGS += -I/usr/include/nodejs/src
JSecrypt_CFLAGS += -I/usr/include/nodejs/deps/v8/include
endif

else # ifdef NPM_VERSION

FMT_FIXUP += $(JSecrypt_OBJ)/warning_fixup
FMT_CHECK += $(JSecrypt_OBJ)/warning_check

$(JSecrypt_OBJ)/warning_fixup:
	$(warning NodeJS not installed, Jsecrypt code will not be formatted)

$(JSecrypt_OBJ)/warning_check:
	$(warning NodeJS not installed, Jsecrypt code will not be checked)

endif # ifdef NPM_VERSION

$(BUILD_PATH)/jsecrypt.tgz: $(JSecrypt_SOURCES) $(JSecrypt_HEADERS) $(JSecrypt_PACKAGE)
	@cd $(BUILD_PATH) && npm pack $(abspath $(JSecrypt_SRC)) > /dev/null
	@mv $(BUILD_PATH)/jsecrypt-*.tgz $(BUILD_PATH)/jsecrypt.tgz
	@echo $(BUILD_PATH)/jsecrypt.tgz

jsecrypt: $(BUILD_PATH)/jsecrypt.tgz

jsecrypt_install: CMD = npm install $(abspath $(BUILD_PATH)/jsecrypt.tgz)
jsecrypt_install: $(BUILD_PATH)/jsecrypt.tgz
ifdef NPM_VERSION
	@echo -n "jsecrypt install "
	@$(BUILD_CMD_)
else
	@echo "Error: npm not found"
	@exit 1
endif

jsecrypt_uninstall: CMD = npm uninstall jsecrypt
jsecrypt_uninstall:
ifdef NPM_VERSION
	@echo -n "jsecrypt uninstall "
	@$(BUILD_CMD_)
endif

uninstall: jsecrypt_uninstall
