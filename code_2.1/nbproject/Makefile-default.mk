#
# Generated Makefile - do not edit!
#
# Edit the Makefile in the project folder instead (../Makefile). Each target
# has a -pre and a -post target defined where you can add customized code.
#
# This makefile implements configuration specific macros and targets.


# Include project Makefile
ifeq "${IGNORE_LOCAL}" "TRUE"
# do not include local makefile. User is passing all local related variables already
else
include Makefile
# Include makefile containing local settings
ifeq "$(wildcard nbproject/Makefile-local-default.mk)" "nbproject/Makefile-local-default.mk"
include nbproject/Makefile-local-default.mk
endif
endif

# Environment
MKDIR=gnumkdir -p
RM=rm -f 
MV=mv 
CP=cp 

# Macros
CND_CONF=default
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
IMAGE_TYPE=debug
OUTPUT_SUFFIX=elf
DEBUGGABLE_SUFFIX=elf
FINAL_IMAGE=${DISTDIR}/code_2.1.${IMAGE_TYPE}.${OUTPUT_SUFFIX}
else
IMAGE_TYPE=production
OUTPUT_SUFFIX=hex
DEBUGGABLE_SUFFIX=elf
FINAL_IMAGE=${DISTDIR}/code_2.1.${IMAGE_TYPE}.${OUTPUT_SUFFIX}
endif

ifeq ($(COMPARE_BUILD), true)
COMPARISON_BUILD=-mafrlcsj
else
COMPARISON_BUILD=
endif

# Object Directory
OBJECTDIR=build/${CND_CONF}/${IMAGE_TYPE}

# Distribution Directory
DISTDIR=dist/${CND_CONF}/${IMAGE_TYPE}

# Source Files Quoted if spaced
SOURCEFILES_QUOTED_IF_SPACED=Source/startup_atsamc21a.c Source/main.c Source/system.c Source/port.c Source/uart.c Source/timer.c Source/analog.c Source/cal_temp.c Source/dac.c Source/flash.c Source/systick.c

# Object Files Quoted if spaced
OBJECTFILES_QUOTED_IF_SPACED=${OBJECTDIR}/Source/startup_atsamc21a.o ${OBJECTDIR}/Source/main.o ${OBJECTDIR}/Source/system.o ${OBJECTDIR}/Source/port.o ${OBJECTDIR}/Source/uart.o ${OBJECTDIR}/Source/timer.o ${OBJECTDIR}/Source/analog.o ${OBJECTDIR}/Source/cal_temp.o ${OBJECTDIR}/Source/dac.o ${OBJECTDIR}/Source/flash.o ${OBJECTDIR}/Source/systick.o
POSSIBLE_DEPFILES=${OBJECTDIR}/Source/startup_atsamc21a.o.d ${OBJECTDIR}/Source/main.o.d ${OBJECTDIR}/Source/system.o.d ${OBJECTDIR}/Source/port.o.d ${OBJECTDIR}/Source/uart.o.d ${OBJECTDIR}/Source/timer.o.d ${OBJECTDIR}/Source/analog.o.d ${OBJECTDIR}/Source/cal_temp.o.d ${OBJECTDIR}/Source/dac.o.d ${OBJECTDIR}/Source/flash.o.d ${OBJECTDIR}/Source/systick.o.d

# Object Files
OBJECTFILES=${OBJECTDIR}/Source/startup_atsamc21a.o ${OBJECTDIR}/Source/main.o ${OBJECTDIR}/Source/system.o ${OBJECTDIR}/Source/port.o ${OBJECTDIR}/Source/uart.o ${OBJECTDIR}/Source/timer.o ${OBJECTDIR}/Source/analog.o ${OBJECTDIR}/Source/cal_temp.o ${OBJECTDIR}/Source/dac.o ${OBJECTDIR}/Source/flash.o ${OBJECTDIR}/Source/systick.o

# Source Files
SOURCEFILES=Source/startup_atsamc21a.c Source/main.c Source/system.c Source/port.c Source/uart.c Source/timer.c Source/analog.c Source/cal_temp.c Source/dac.c Source/flash.c Source/systick.c

# Pack Options 
PACK_COMMON_OPTIONS=-I "${CMSIS_DIR}/CMSIS/Core/Include"



CFLAGS=
ASFLAGS=
LDLIBSOPTIONS=

############# Tool locations ##########################################
# If you copy a project from one host to another, the path where the  #
# compiler is installed may be different.                             #
# If you open this project with MPLAB X in the new host, this         #
# makefile will be regenerated and the paths will be corrected.       #
#######################################################################
# fixDeps replaces a bunch of sed/cat/printf statements that slow down the build
FIXDEPS=fixDeps

.build-conf:  ${BUILD_SUBPROJECTS}
ifneq ($(INFORMATION_MESSAGE), )
	@echo $(INFORMATION_MESSAGE)
endif
	${MAKE}  -f nbproject/Makefile-default.mk ${DISTDIR}/code_2.1.${IMAGE_TYPE}.${OUTPUT_SUFFIX}

MP_PROCESSOR_OPTION=ATSAMC21E18A
MP_LINKER_FILE_OPTION=,--script="Linker\ATSAMC21E18A.ld"
# ------------------------------------------------------------------------------------
# Rules for buildStep: assemble
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
else
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: assembleWithPreprocess
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
else
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: compile
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
${OBJECTDIR}/Source/startup_atsamc21a.o: Source/startup_atsamc21a.c  .generated_files/flags/default/5476230461b5d98dbea34e8d5f2c2473dcf6ffa4 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/Source" 
	@${RM} ${OBJECTDIR}/Source/startup_atsamc21a.o.d 
	@${RM} ${OBJECTDIR}/Source/startup_atsamc21a.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD4=1  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -fno-common -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/Source/startup_atsamc21a.o.d" -o ${OBJECTDIR}/Source/startup_atsamc21a.o Source/startup_atsamc21a.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}/samc21" ${PACK_COMMON_OPTIONS} 
	
${OBJECTDIR}/Source/main.o: Source/main.c  .generated_files/flags/default/efebd98f979ba0fc47a4e38a7f953c351cfcec3a .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/Source" 
	@${RM} ${OBJECTDIR}/Source/main.o.d 
	@${RM} ${OBJECTDIR}/Source/main.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD4=1  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -fno-common -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/Source/main.o.d" -o ${OBJECTDIR}/Source/main.o Source/main.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}/samc21" ${PACK_COMMON_OPTIONS} 
	
${OBJECTDIR}/Source/system.o: Source/system.c  .generated_files/flags/default/dfce0ee40b939bbc04265511584268951404ac33 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/Source" 
	@${RM} ${OBJECTDIR}/Source/system.o.d 
	@${RM} ${OBJECTDIR}/Source/system.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD4=1  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -fno-common -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/Source/system.o.d" -o ${OBJECTDIR}/Source/system.o Source/system.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}/samc21" ${PACK_COMMON_OPTIONS} 
	
${OBJECTDIR}/Source/port.o: Source/port.c  .generated_files/flags/default/a28f308dd86540815610596cd0c12894ae327998 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/Source" 
	@${RM} ${OBJECTDIR}/Source/port.o.d 
	@${RM} ${OBJECTDIR}/Source/port.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD4=1  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -fno-common -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/Source/port.o.d" -o ${OBJECTDIR}/Source/port.o Source/port.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}/samc21" ${PACK_COMMON_OPTIONS} 
	
${OBJECTDIR}/Source/uart.o: Source/uart.c  .generated_files/flags/default/6e9a296dfdd27dcb37e87b70b4b27d82470b2f26 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/Source" 
	@${RM} ${OBJECTDIR}/Source/uart.o.d 
	@${RM} ${OBJECTDIR}/Source/uart.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD4=1  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -fno-common -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/Source/uart.o.d" -o ${OBJECTDIR}/Source/uart.o Source/uart.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}/samc21" ${PACK_COMMON_OPTIONS} 
	
${OBJECTDIR}/Source/timer.o: Source/timer.c  .generated_files/flags/default/cb94e4172c92908b60864f7304207b72f94ae235 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/Source" 
	@${RM} ${OBJECTDIR}/Source/timer.o.d 
	@${RM} ${OBJECTDIR}/Source/timer.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD4=1  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -fno-common -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/Source/timer.o.d" -o ${OBJECTDIR}/Source/timer.o Source/timer.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}/samc21" ${PACK_COMMON_OPTIONS} 
	
${OBJECTDIR}/Source/analog.o: Source/analog.c  .generated_files/flags/default/2d9af374f5706b94df0d5d00c98df2445228fb4b .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/Source" 
	@${RM} ${OBJECTDIR}/Source/analog.o.d 
	@${RM} ${OBJECTDIR}/Source/analog.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD4=1  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -fno-common -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/Source/analog.o.d" -o ${OBJECTDIR}/Source/analog.o Source/analog.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}/samc21" ${PACK_COMMON_OPTIONS} 
	
${OBJECTDIR}/Source/cal_temp.o: Source/cal_temp.c  .generated_files/flags/default/8b7c1ef1f48de2384a8f733af3d87431e08d4f7e .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/Source" 
	@${RM} ${OBJECTDIR}/Source/cal_temp.o.d 
	@${RM} ${OBJECTDIR}/Source/cal_temp.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD4=1  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -fno-common -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/Source/cal_temp.o.d" -o ${OBJECTDIR}/Source/cal_temp.o Source/cal_temp.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}/samc21" ${PACK_COMMON_OPTIONS} 
	
${OBJECTDIR}/Source/dac.o: Source/dac.c  .generated_files/flags/default/7695c534a9a37b7900befc039b98b73740999578 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/Source" 
	@${RM} ${OBJECTDIR}/Source/dac.o.d 
	@${RM} ${OBJECTDIR}/Source/dac.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD4=1  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -fno-common -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/Source/dac.o.d" -o ${OBJECTDIR}/Source/dac.o Source/dac.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}/samc21" ${PACK_COMMON_OPTIONS} 
	
${OBJECTDIR}/Source/flash.o: Source/flash.c  .generated_files/flags/default/a8150149accbda09f9f6aaa07e7cfb519a676252 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/Source" 
	@${RM} ${OBJECTDIR}/Source/flash.o.d 
	@${RM} ${OBJECTDIR}/Source/flash.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD4=1  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -fno-common -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/Source/flash.o.d" -o ${OBJECTDIR}/Source/flash.o Source/flash.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}/samc21" ${PACK_COMMON_OPTIONS} 
	
${OBJECTDIR}/Source/systick.o: Source/systick.c  .generated_files/flags/default/a78f49a52549e98efe3fd4becc8c46e95902c152 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/Source" 
	@${RM} ${OBJECTDIR}/Source/systick.o.d 
	@${RM} ${OBJECTDIR}/Source/systick.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD4=1  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -fno-common -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/Source/systick.o.d" -o ${OBJECTDIR}/Source/systick.o Source/systick.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}/samc21" ${PACK_COMMON_OPTIONS} 
	
else
${OBJECTDIR}/Source/startup_atsamc21a.o: Source/startup_atsamc21a.c  .generated_files/flags/default/79112143d465be77e71a260dbc3a3242d869b976 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/Source" 
	@${RM} ${OBJECTDIR}/Source/startup_atsamc21a.o.d 
	@${RM} ${OBJECTDIR}/Source/startup_atsamc21a.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -fno-common -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/Source/startup_atsamc21a.o.d" -o ${OBJECTDIR}/Source/startup_atsamc21a.o Source/startup_atsamc21a.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}/samc21" ${PACK_COMMON_OPTIONS} 
	
${OBJECTDIR}/Source/main.o: Source/main.c  .generated_files/flags/default/758af32f0f07791fdc752a05d63d43b2cfd1cd5b .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/Source" 
	@${RM} ${OBJECTDIR}/Source/main.o.d 
	@${RM} ${OBJECTDIR}/Source/main.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -fno-common -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/Source/main.o.d" -o ${OBJECTDIR}/Source/main.o Source/main.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}/samc21" ${PACK_COMMON_OPTIONS} 
	
${OBJECTDIR}/Source/system.o: Source/system.c  .generated_files/flags/default/a152007166d9e6b5cfd0ad0b385d31044be44f27 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/Source" 
	@${RM} ${OBJECTDIR}/Source/system.o.d 
	@${RM} ${OBJECTDIR}/Source/system.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -fno-common -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/Source/system.o.d" -o ${OBJECTDIR}/Source/system.o Source/system.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}/samc21" ${PACK_COMMON_OPTIONS} 
	
${OBJECTDIR}/Source/port.o: Source/port.c  .generated_files/flags/default/5f3a0b2e70a17857238c24755d3767c4340d6251 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/Source" 
	@${RM} ${OBJECTDIR}/Source/port.o.d 
	@${RM} ${OBJECTDIR}/Source/port.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -fno-common -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/Source/port.o.d" -o ${OBJECTDIR}/Source/port.o Source/port.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}/samc21" ${PACK_COMMON_OPTIONS} 
	
${OBJECTDIR}/Source/uart.o: Source/uart.c  .generated_files/flags/default/d28745cbcd85bdcbc450d2a3b13b65d5f7bff004 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/Source" 
	@${RM} ${OBJECTDIR}/Source/uart.o.d 
	@${RM} ${OBJECTDIR}/Source/uart.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -fno-common -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/Source/uart.o.d" -o ${OBJECTDIR}/Source/uart.o Source/uart.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}/samc21" ${PACK_COMMON_OPTIONS} 
	
${OBJECTDIR}/Source/timer.o: Source/timer.c  .generated_files/flags/default/883249e1d230b4b739e629ac9e1cc3d6941234f7 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/Source" 
	@${RM} ${OBJECTDIR}/Source/timer.o.d 
	@${RM} ${OBJECTDIR}/Source/timer.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -fno-common -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/Source/timer.o.d" -o ${OBJECTDIR}/Source/timer.o Source/timer.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}/samc21" ${PACK_COMMON_OPTIONS} 
	
${OBJECTDIR}/Source/analog.o: Source/analog.c  .generated_files/flags/default/10604e76d189ccbeb5ed4f31bc2e0b6556a165b6 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/Source" 
	@${RM} ${OBJECTDIR}/Source/analog.o.d 
	@${RM} ${OBJECTDIR}/Source/analog.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -fno-common -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/Source/analog.o.d" -o ${OBJECTDIR}/Source/analog.o Source/analog.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}/samc21" ${PACK_COMMON_OPTIONS} 
	
${OBJECTDIR}/Source/cal_temp.o: Source/cal_temp.c  .generated_files/flags/default/5c741034a5d7f63440e3ccb38f2f3badc3ca2d7d .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/Source" 
	@${RM} ${OBJECTDIR}/Source/cal_temp.o.d 
	@${RM} ${OBJECTDIR}/Source/cal_temp.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -fno-common -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/Source/cal_temp.o.d" -o ${OBJECTDIR}/Source/cal_temp.o Source/cal_temp.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}/samc21" ${PACK_COMMON_OPTIONS} 
	
${OBJECTDIR}/Source/dac.o: Source/dac.c  .generated_files/flags/default/72856688f93c947e0331a0a82065bb29893feb1f .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/Source" 
	@${RM} ${OBJECTDIR}/Source/dac.o.d 
	@${RM} ${OBJECTDIR}/Source/dac.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -fno-common -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/Source/dac.o.d" -o ${OBJECTDIR}/Source/dac.o Source/dac.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}/samc21" ${PACK_COMMON_OPTIONS} 
	
${OBJECTDIR}/Source/flash.o: Source/flash.c  .generated_files/flags/default/ce612aae409c60edbe454396438427ff5571675 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/Source" 
	@${RM} ${OBJECTDIR}/Source/flash.o.d 
	@${RM} ${OBJECTDIR}/Source/flash.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -fno-common -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/Source/flash.o.d" -o ${OBJECTDIR}/Source/flash.o Source/flash.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}/samc21" ${PACK_COMMON_OPTIONS} 
	
${OBJECTDIR}/Source/systick.o: Source/systick.c  .generated_files/flags/default/3a4ddd57110d9a9d33ad9103641415178e643f88 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/Source" 
	@${RM} ${OBJECTDIR}/Source/systick.o.d 
	@${RM} ${OBJECTDIR}/Source/systick.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -fno-common -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/Source/systick.o.d" -o ${OBJECTDIR}/Source/systick.o Source/systick.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}/samc21" ${PACK_COMMON_OPTIONS} 
	
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: compileCPP
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
else
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: link
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
${DISTDIR}/code_2.1.${IMAGE_TYPE}.${OUTPUT_SUFFIX}: ${OBJECTFILES}  nbproject/Makefile-${CND_CONF}.mk    Linker/ATSAMC21E18A.ld
	@${MKDIR} ${DISTDIR} 
	${MP_CC} $(MP_EXTRA_LD_PRE) -g  -D__MPLAB_DEBUGGER_ICD4=1 -mprocessor=$(MP_PROCESSOR_OPTION)  -o ${DISTDIR}/code_2.1.${IMAGE_TYPE}.${OUTPUT_SUFFIX} ${OBJECTFILES_QUOTED_IF_SPACED}          -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -Wl,--defsym=__MPLAB_BUILD=1$(MP_EXTRA_LD_POST)$(MP_LINKER_FILE_OPTION),--defsym=__ICD2RAM=1,--defsym=__MPLAB_DEBUG=1,--defsym=__DEBUG=1,-D=__DEBUG_D,--defsym=__MPLAB_DEBUGGER_ICD4=1,--defsym=_min_heap_size=512,--gc-sections,-Map="${DISTDIR}/${PROJECTNAME}.${IMAGE_TYPE}.map",--memorysummary,${DISTDIR}/memoryfile.xml,-T,Linker/ATSAMC21E18A.ld,,-lm,-u,_printf_float, -mdfp="${DFP_DIR}/samc21"
	
else
${DISTDIR}/code_2.1.${IMAGE_TYPE}.${OUTPUT_SUFFIX}: ${OBJECTFILES}  nbproject/Makefile-${CND_CONF}.mk   Linker/ATSAMC21E18A.ld
	@${MKDIR} ${DISTDIR} 
	${MP_CC} $(MP_EXTRA_LD_PRE)  -mprocessor=$(MP_PROCESSOR_OPTION)  -o ${DISTDIR}/code_2.1.${IMAGE_TYPE}.${DEBUGGABLE_SUFFIX} ${OBJECTFILES_QUOTED_IF_SPACED}          -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -Wl,--defsym=__MPLAB_BUILD=1$(MP_EXTRA_LD_POST)$(MP_LINKER_FILE_OPTION),--defsym=_min_heap_size=512,--gc-sections,-Map="${DISTDIR}/${PROJECTNAME}.${IMAGE_TYPE}.map",--memorysummary,${DISTDIR}/memoryfile.xml,-T,Linker/ATSAMC21E18A.ld,,-lm,-u,_printf_float, -mdfp="${DFP_DIR}/samc21"
	${MP_CC_DIR}\\xc32-bin2hex ${DISTDIR}/code_2.1.${IMAGE_TYPE}.${DEBUGGABLE_SUFFIX} 
endif


# Subprojects
.build-subprojects:


# Subprojects
.clean-subprojects:

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS}
	${RM} -r ${OBJECTDIR}
	${RM} -r ${DISTDIR}

# Enable dependency checking
.dep.inc: .depcheck-impl

DEPFILES=$(wildcard ${POSSIBLE_DEPFILES})
ifneq (${DEPFILES},)
include ${DEPFILES}
endif
