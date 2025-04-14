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
FINAL_IMAGE=${DISTDIR}/code_3.1.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}
else
IMAGE_TYPE=production
OUTPUT_SUFFIX=hex
DEBUGGABLE_SUFFIX=elf
FINAL_IMAGE=${DISTDIR}/code_3.1.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}
endif

ifeq ($(COMPARE_BUILD), true)
COMPARISON_BUILD=
else
COMPARISON_BUILD=
endif

# Object Directory
OBJECTDIR=build/${CND_CONF}/${IMAGE_TYPE}

# Distribution Directory
DISTDIR=dist/${CND_CONF}/${IMAGE_TYPE}

# Source Files Quoted if spaced
SOURCEFILES_QUOTED_IF_SPACED=startup_samc21e18a.c system_samc21e18a.c main.c analog.c cal_temp.c dac.c fis.c flash.c port.c spi.c system.c systick.c timer.c uart.c

# Object Files Quoted if spaced
OBJECTFILES_QUOTED_IF_SPACED=${OBJECTDIR}/startup_samc21e18a.o ${OBJECTDIR}/system_samc21e18a.o ${OBJECTDIR}/main.o ${OBJECTDIR}/analog.o ${OBJECTDIR}/cal_temp.o ${OBJECTDIR}/dac.o ${OBJECTDIR}/fis.o ${OBJECTDIR}/flash.o ${OBJECTDIR}/port.o ${OBJECTDIR}/spi.o ${OBJECTDIR}/system.o ${OBJECTDIR}/systick.o ${OBJECTDIR}/timer.o ${OBJECTDIR}/uart.o
POSSIBLE_DEPFILES=${OBJECTDIR}/startup_samc21e18a.o.d ${OBJECTDIR}/system_samc21e18a.o.d ${OBJECTDIR}/main.o.d ${OBJECTDIR}/analog.o.d ${OBJECTDIR}/cal_temp.o.d ${OBJECTDIR}/dac.o.d ${OBJECTDIR}/fis.o.d ${OBJECTDIR}/flash.o.d ${OBJECTDIR}/port.o.d ${OBJECTDIR}/spi.o.d ${OBJECTDIR}/system.o.d ${OBJECTDIR}/systick.o.d ${OBJECTDIR}/timer.o.d ${OBJECTDIR}/uart.o.d

# Object Files
OBJECTFILES=${OBJECTDIR}/startup_samc21e18a.o ${OBJECTDIR}/system_samc21e18a.o ${OBJECTDIR}/main.o ${OBJECTDIR}/analog.o ${OBJECTDIR}/cal_temp.o ${OBJECTDIR}/dac.o ${OBJECTDIR}/fis.o ${OBJECTDIR}/flash.o ${OBJECTDIR}/port.o ${OBJECTDIR}/spi.o ${OBJECTDIR}/system.o ${OBJECTDIR}/systick.o ${OBJECTDIR}/timer.o ${OBJECTDIR}/uart.o

# Source Files
SOURCEFILES=startup_samc21e18a.c system_samc21e18a.c main.c analog.c cal_temp.c dac.c fis.c flash.c port.c spi.c system.c systick.c timer.c uart.c

# Pack Options 
PACK_COMMON_OPTIONS=-I "${DFP_DIR}/samc21/include"  -I "${CMSIS_DIR}/CMSIS/Core/Include"



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
	${MAKE}  -f nbproject/Makefile-default.mk ${DISTDIR}/code_3.1.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}

MP_PROCESSOR_OPTION=SAMC21E18A
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
${OBJECTDIR}/startup_samc21e18a.o: startup_samc21e18a.c  .generated_files/flags/default/df9a87efc79b105390e20c217cb71de0eef7a68c .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/startup_samc21e18a.o.d 
	@${RM} ${OBJECTDIR}/startup_samc21e18a.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -mcpu=cortex-m0plus -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD4=1 -gdwarf-2  -x c -c -D__$(MP_PROCESSOR_OPTION)__  -mthumb ${PACK_COMMON_OPTIONS}  -ffunction-sections -mlong-calls -Wall -MP -MMD -MF "${OBJECTDIR}/startup_samc21e18a.o.d" -o ${OBJECTDIR}/startup_samc21e18a.o startup_samc21e18a.c  -DXPRJ_default=$(CND_CONF)  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/system_samc21e18a.o: system_samc21e18a.c  .generated_files/flags/default/7784847e8e3b2a5d3aaed1e7c59cd2654539bd60 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/system_samc21e18a.o.d 
	@${RM} ${OBJECTDIR}/system_samc21e18a.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -mcpu=cortex-m0plus -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD4=1 -gdwarf-2  -x c -c -D__$(MP_PROCESSOR_OPTION)__  -mthumb ${PACK_COMMON_OPTIONS}  -ffunction-sections -mlong-calls -Wall -MP -MMD -MF "${OBJECTDIR}/system_samc21e18a.o.d" -o ${OBJECTDIR}/system_samc21e18a.o system_samc21e18a.c  -DXPRJ_default=$(CND_CONF)  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/main.o: main.c  .generated_files/flags/default/c5007d24bc3cd43e16df9603dbd3ea8ead4fe4d4 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/main.o.d 
	@${RM} ${OBJECTDIR}/main.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -mcpu=cortex-m0plus -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD4=1 -gdwarf-2  -x c -c -D__$(MP_PROCESSOR_OPTION)__  -mthumb ${PACK_COMMON_OPTIONS}  -ffunction-sections -mlong-calls -Wall -MP -MMD -MF "${OBJECTDIR}/main.o.d" -o ${OBJECTDIR}/main.o main.c  -DXPRJ_default=$(CND_CONF)  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/analog.o: analog.c  .generated_files/flags/default/186c019aa4b51ef547506bdce5f9c7f9fa707024 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/analog.o.d 
	@${RM} ${OBJECTDIR}/analog.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -mcpu=cortex-m0plus -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD4=1 -gdwarf-2  -x c -c -D__$(MP_PROCESSOR_OPTION)__  -mthumb ${PACK_COMMON_OPTIONS}  -ffunction-sections -mlong-calls -Wall -MP -MMD -MF "${OBJECTDIR}/analog.o.d" -o ${OBJECTDIR}/analog.o analog.c  -DXPRJ_default=$(CND_CONF)  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/cal_temp.o: cal_temp.c  .generated_files/flags/default/4d0c5bc756e021f27ec4785f6cc125a9ae683b95 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/cal_temp.o.d 
	@${RM} ${OBJECTDIR}/cal_temp.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -mcpu=cortex-m0plus -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD4=1 -gdwarf-2  -x c -c -D__$(MP_PROCESSOR_OPTION)__  -mthumb ${PACK_COMMON_OPTIONS}  -ffunction-sections -mlong-calls -Wall -MP -MMD -MF "${OBJECTDIR}/cal_temp.o.d" -o ${OBJECTDIR}/cal_temp.o cal_temp.c  -DXPRJ_default=$(CND_CONF)  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/dac.o: dac.c  .generated_files/flags/default/136ac15323f4bfb0ac97de2d2360d673f202b8e4 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/dac.o.d 
	@${RM} ${OBJECTDIR}/dac.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -mcpu=cortex-m0plus -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD4=1 -gdwarf-2  -x c -c -D__$(MP_PROCESSOR_OPTION)__  -mthumb ${PACK_COMMON_OPTIONS}  -ffunction-sections -mlong-calls -Wall -MP -MMD -MF "${OBJECTDIR}/dac.o.d" -o ${OBJECTDIR}/dac.o dac.c  -DXPRJ_default=$(CND_CONF)  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/fis.o: fis.c  .generated_files/flags/default/c3ce5c541177241caf8b469d827fd681f8a70ba .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/fis.o.d 
	@${RM} ${OBJECTDIR}/fis.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -mcpu=cortex-m0plus -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD4=1 -gdwarf-2  -x c -c -D__$(MP_PROCESSOR_OPTION)__  -mthumb ${PACK_COMMON_OPTIONS}  -ffunction-sections -mlong-calls -Wall -MP -MMD -MF "${OBJECTDIR}/fis.o.d" -o ${OBJECTDIR}/fis.o fis.c  -DXPRJ_default=$(CND_CONF)  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/flash.o: flash.c  .generated_files/flags/default/6aca991a359f3e3920755ea291702e57cc7928c7 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/flash.o.d 
	@${RM} ${OBJECTDIR}/flash.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -mcpu=cortex-m0plus -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD4=1 -gdwarf-2  -x c -c -D__$(MP_PROCESSOR_OPTION)__  -mthumb ${PACK_COMMON_OPTIONS}  -ffunction-sections -mlong-calls -Wall -MP -MMD -MF "${OBJECTDIR}/flash.o.d" -o ${OBJECTDIR}/flash.o flash.c  -DXPRJ_default=$(CND_CONF)  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/port.o: port.c  .generated_files/flags/default/822dff3fd23eddff77af5e82dea4ddca5626c54a .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/port.o.d 
	@${RM} ${OBJECTDIR}/port.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -mcpu=cortex-m0plus -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD4=1 -gdwarf-2  -x c -c -D__$(MP_PROCESSOR_OPTION)__  -mthumb ${PACK_COMMON_OPTIONS}  -ffunction-sections -mlong-calls -Wall -MP -MMD -MF "${OBJECTDIR}/port.o.d" -o ${OBJECTDIR}/port.o port.c  -DXPRJ_default=$(CND_CONF)  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/spi.o: spi.c  .generated_files/flags/default/ec5f99999c1d3108511d4e7c44ce3a882bc96e4b .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/spi.o.d 
	@${RM} ${OBJECTDIR}/spi.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -mcpu=cortex-m0plus -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD4=1 -gdwarf-2  -x c -c -D__$(MP_PROCESSOR_OPTION)__  -mthumb ${PACK_COMMON_OPTIONS}  -ffunction-sections -mlong-calls -Wall -MP -MMD -MF "${OBJECTDIR}/spi.o.d" -o ${OBJECTDIR}/spi.o spi.c  -DXPRJ_default=$(CND_CONF)  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/system.o: system.c  .generated_files/flags/default/37f49b1eae5b772196414308cd650c77bf2173d0 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/system.o.d 
	@${RM} ${OBJECTDIR}/system.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -mcpu=cortex-m0plus -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD4=1 -gdwarf-2  -x c -c -D__$(MP_PROCESSOR_OPTION)__  -mthumb ${PACK_COMMON_OPTIONS}  -ffunction-sections -mlong-calls -Wall -MP -MMD -MF "${OBJECTDIR}/system.o.d" -o ${OBJECTDIR}/system.o system.c  -DXPRJ_default=$(CND_CONF)  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/systick.o: systick.c  .generated_files/flags/default/3d763611de56c65f074b74d950c9a3382c4fb643 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/systick.o.d 
	@${RM} ${OBJECTDIR}/systick.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -mcpu=cortex-m0plus -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD4=1 -gdwarf-2  -x c -c -D__$(MP_PROCESSOR_OPTION)__  -mthumb ${PACK_COMMON_OPTIONS}  -ffunction-sections -mlong-calls -Wall -MP -MMD -MF "${OBJECTDIR}/systick.o.d" -o ${OBJECTDIR}/systick.o systick.c  -DXPRJ_default=$(CND_CONF)  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/timer.o: timer.c  .generated_files/flags/default/380e263842eb51df142198d27d75421e2891a7fa .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/timer.o.d 
	@${RM} ${OBJECTDIR}/timer.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -mcpu=cortex-m0plus -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD4=1 -gdwarf-2  -x c -c -D__$(MP_PROCESSOR_OPTION)__  -mthumb ${PACK_COMMON_OPTIONS}  -ffunction-sections -mlong-calls -Wall -MP -MMD -MF "${OBJECTDIR}/timer.o.d" -o ${OBJECTDIR}/timer.o timer.c  -DXPRJ_default=$(CND_CONF)  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/uart.o: uart.c  .generated_files/flags/default/202bd00e22a17d3943f31ba490acaed6c9ffc9c8 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/uart.o.d 
	@${RM} ${OBJECTDIR}/uart.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -mcpu=cortex-m0plus -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD4=1 -gdwarf-2  -x c -c -D__$(MP_PROCESSOR_OPTION)__  -mthumb ${PACK_COMMON_OPTIONS}  -ffunction-sections -mlong-calls -Wall -MP -MMD -MF "${OBJECTDIR}/uart.o.d" -o ${OBJECTDIR}/uart.o uart.c  -DXPRJ_default=$(CND_CONF)  $(COMPARISON_BUILD) 
	
else
${OBJECTDIR}/startup_samc21e18a.o: startup_samc21e18a.c  .generated_files/flags/default/e34b52b0d797a0b5562808a0af2604395396a44b .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/startup_samc21e18a.o.d 
	@${RM} ${OBJECTDIR}/startup_samc21e18a.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -mcpu=cortex-m0plus  -x c -c -D__$(MP_PROCESSOR_OPTION)__  -mthumb ${PACK_COMMON_OPTIONS}  -ffunction-sections -mlong-calls -Wall -MP -MMD -MF "${OBJECTDIR}/startup_samc21e18a.o.d" -o ${OBJECTDIR}/startup_samc21e18a.o startup_samc21e18a.c  -DXPRJ_default=$(CND_CONF)  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/system_samc21e18a.o: system_samc21e18a.c  .generated_files/flags/default/f507782007cda1571ba4fcef9527c420b6a754db .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/system_samc21e18a.o.d 
	@${RM} ${OBJECTDIR}/system_samc21e18a.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -mcpu=cortex-m0plus  -x c -c -D__$(MP_PROCESSOR_OPTION)__  -mthumb ${PACK_COMMON_OPTIONS}  -ffunction-sections -mlong-calls -Wall -MP -MMD -MF "${OBJECTDIR}/system_samc21e18a.o.d" -o ${OBJECTDIR}/system_samc21e18a.o system_samc21e18a.c  -DXPRJ_default=$(CND_CONF)  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/main.o: main.c  .generated_files/flags/default/2857c0343e12a5eb4b411565212212ca16e90839 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/main.o.d 
	@${RM} ${OBJECTDIR}/main.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -mcpu=cortex-m0plus  -x c -c -D__$(MP_PROCESSOR_OPTION)__  -mthumb ${PACK_COMMON_OPTIONS}  -ffunction-sections -mlong-calls -Wall -MP -MMD -MF "${OBJECTDIR}/main.o.d" -o ${OBJECTDIR}/main.o main.c  -DXPRJ_default=$(CND_CONF)  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/analog.o: analog.c  .generated_files/flags/default/5fdad023dbef58202943a194f7e69694830ada0f .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/analog.o.d 
	@${RM} ${OBJECTDIR}/analog.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -mcpu=cortex-m0plus  -x c -c -D__$(MP_PROCESSOR_OPTION)__  -mthumb ${PACK_COMMON_OPTIONS}  -ffunction-sections -mlong-calls -Wall -MP -MMD -MF "${OBJECTDIR}/analog.o.d" -o ${OBJECTDIR}/analog.o analog.c  -DXPRJ_default=$(CND_CONF)  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/cal_temp.o: cal_temp.c  .generated_files/flags/default/8eb8c18ff714ba1a24172af19deabf687d7243c7 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/cal_temp.o.d 
	@${RM} ${OBJECTDIR}/cal_temp.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -mcpu=cortex-m0plus  -x c -c -D__$(MP_PROCESSOR_OPTION)__  -mthumb ${PACK_COMMON_OPTIONS}  -ffunction-sections -mlong-calls -Wall -MP -MMD -MF "${OBJECTDIR}/cal_temp.o.d" -o ${OBJECTDIR}/cal_temp.o cal_temp.c  -DXPRJ_default=$(CND_CONF)  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/dac.o: dac.c  .generated_files/flags/default/6f3ce1d398df284041c0f71aa3ed1650a84469ee .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/dac.o.d 
	@${RM} ${OBJECTDIR}/dac.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -mcpu=cortex-m0plus  -x c -c -D__$(MP_PROCESSOR_OPTION)__  -mthumb ${PACK_COMMON_OPTIONS}  -ffunction-sections -mlong-calls -Wall -MP -MMD -MF "${OBJECTDIR}/dac.o.d" -o ${OBJECTDIR}/dac.o dac.c  -DXPRJ_default=$(CND_CONF)  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/fis.o: fis.c  .generated_files/flags/default/b124edcf3be839be5f826d89b0c70e6047862ba3 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/fis.o.d 
	@${RM} ${OBJECTDIR}/fis.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -mcpu=cortex-m0plus  -x c -c -D__$(MP_PROCESSOR_OPTION)__  -mthumb ${PACK_COMMON_OPTIONS}  -ffunction-sections -mlong-calls -Wall -MP -MMD -MF "${OBJECTDIR}/fis.o.d" -o ${OBJECTDIR}/fis.o fis.c  -DXPRJ_default=$(CND_CONF)  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/flash.o: flash.c  .generated_files/flags/default/9bfb383ab3fecb4ea87ae48af38ecf6acca4ffb8 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/flash.o.d 
	@${RM} ${OBJECTDIR}/flash.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -mcpu=cortex-m0plus  -x c -c -D__$(MP_PROCESSOR_OPTION)__  -mthumb ${PACK_COMMON_OPTIONS}  -ffunction-sections -mlong-calls -Wall -MP -MMD -MF "${OBJECTDIR}/flash.o.d" -o ${OBJECTDIR}/flash.o flash.c  -DXPRJ_default=$(CND_CONF)  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/port.o: port.c  .generated_files/flags/default/678421d2139b4ad31fd331f61981c88c2f4fcff6 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/port.o.d 
	@${RM} ${OBJECTDIR}/port.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -mcpu=cortex-m0plus  -x c -c -D__$(MP_PROCESSOR_OPTION)__  -mthumb ${PACK_COMMON_OPTIONS}  -ffunction-sections -mlong-calls -Wall -MP -MMD -MF "${OBJECTDIR}/port.o.d" -o ${OBJECTDIR}/port.o port.c  -DXPRJ_default=$(CND_CONF)  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/spi.o: spi.c  .generated_files/flags/default/8460da417427d05519dd275568deaf435771a878 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/spi.o.d 
	@${RM} ${OBJECTDIR}/spi.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -mcpu=cortex-m0plus  -x c -c -D__$(MP_PROCESSOR_OPTION)__  -mthumb ${PACK_COMMON_OPTIONS}  -ffunction-sections -mlong-calls -Wall -MP -MMD -MF "${OBJECTDIR}/spi.o.d" -o ${OBJECTDIR}/spi.o spi.c  -DXPRJ_default=$(CND_CONF)  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/system.o: system.c  .generated_files/flags/default/aecef50f7cb881c6634fe4688446c7d13cb279a4 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/system.o.d 
	@${RM} ${OBJECTDIR}/system.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -mcpu=cortex-m0plus  -x c -c -D__$(MP_PROCESSOR_OPTION)__  -mthumb ${PACK_COMMON_OPTIONS}  -ffunction-sections -mlong-calls -Wall -MP -MMD -MF "${OBJECTDIR}/system.o.d" -o ${OBJECTDIR}/system.o system.c  -DXPRJ_default=$(CND_CONF)  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/systick.o: systick.c  .generated_files/flags/default/bc0e1b816c81adbb01608f20cbcb6f7dc6dd6239 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/systick.o.d 
	@${RM} ${OBJECTDIR}/systick.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -mcpu=cortex-m0plus  -x c -c -D__$(MP_PROCESSOR_OPTION)__  -mthumb ${PACK_COMMON_OPTIONS}  -ffunction-sections -mlong-calls -Wall -MP -MMD -MF "${OBJECTDIR}/systick.o.d" -o ${OBJECTDIR}/systick.o systick.c  -DXPRJ_default=$(CND_CONF)  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/timer.o: timer.c  .generated_files/flags/default/6ef12edae5a072583d1c86d177cd39dc4f4dced8 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/timer.o.d 
	@${RM} ${OBJECTDIR}/timer.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -mcpu=cortex-m0plus  -x c -c -D__$(MP_PROCESSOR_OPTION)__  -mthumb ${PACK_COMMON_OPTIONS}  -ffunction-sections -mlong-calls -Wall -MP -MMD -MF "${OBJECTDIR}/timer.o.d" -o ${OBJECTDIR}/timer.o timer.c  -DXPRJ_default=$(CND_CONF)  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/uart.o: uart.c  .generated_files/flags/default/5ebe088787c687800e11eaeae41a488feae2a0e4 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/uart.o.d 
	@${RM} ${OBJECTDIR}/uart.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -mcpu=cortex-m0plus  -x c -c -D__$(MP_PROCESSOR_OPTION)__  -mthumb ${PACK_COMMON_OPTIONS}  -ffunction-sections -mlong-calls -Wall -MP -MMD -MF "${OBJECTDIR}/uart.o.d" -o ${OBJECTDIR}/uart.o uart.c  -DXPRJ_default=$(CND_CONF)  $(COMPARISON_BUILD) 
	
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: compileCPP
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
else
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: link
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
${DISTDIR}/code_3.1.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}: ${OBJECTFILES}  nbproject/Makefile-${CND_CONF}.mk    samc21e18a_flash.ld
	@${MKDIR} ${DISTDIR} 
	${MP_CC} $(MP_EXTRA_LD_PRE) -mcpu=cortex-m0plus  -D__MPLAB_DEBUGGER_ICD4=1 -gdwarf-2  -D__$(MP_PROCESSOR_OPTION)__   -T"samc21e18a_flash.ld"  -mthumb --specs=nosys.specs -Wl,-Map="${DISTDIR}\code_3.1.X.${IMAGE_TYPE}.map"  -o ${DISTDIR}/code_3.1.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX} ${OBJECTFILES_QUOTED_IF_SPACED}      -DXPRJ_default=$(CND_CONF)  $(COMPARISON_BUILD)  -Wl,--defsym=__MPLAB_BUILD=1$(MP_EXTRA_LD_POST)$(MP_LINKER_FILE_OPTION),--defsym=__ICD2RAM=1,--defsym=__MPLAB_DEBUG=1,--defsym=__DEBUG=1,--defsym=__MPLAB_DEBUGGER_ICD4=1 -Wl,--gc-sections   -Wl,--print-memory-usage -Wl,--defsym=__printf_float=1 -lm 
	
	
	
	
	
	
else
${DISTDIR}/code_3.1.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}: ${OBJECTFILES}  nbproject/Makefile-${CND_CONF}.mk   samc21e18a_flash.ld
	@${MKDIR} ${DISTDIR} 
	${MP_CC} $(MP_EXTRA_LD_PRE) -mcpu=cortex-m0plus  -D__$(MP_PROCESSOR_OPTION)__   -T"samc21e18a_flash.ld"  -mthumb --specs=nosys.specs -Wl,-Map="${DISTDIR}\code_3.1.X.${IMAGE_TYPE}.map"  -o ${DISTDIR}/code_3.1.X.${IMAGE_TYPE}.${DEBUGGABLE_SUFFIX} ${OBJECTFILES_QUOTED_IF_SPACED}      -DXPRJ_default=$(CND_CONF)  $(COMPARISON_BUILD)  -Wl,--defsym=__MPLAB_BUILD=1$(MP_EXTRA_LD_POST)$(MP_LINKER_FILE_OPTION) -Wl,--gc-sections   -Wl,--print-memory-usage -Wl,--defsym=__printf_float=1 -lm 
	
	${MP_CC_DIR}\\arm-none-eabi-objcopy -O ihex -R .eeprom -R .fuse -R .lock -R .signature "${DISTDIR}/code_3.1.X.${IMAGE_TYPE}.${DEBUGGABLE_SUFFIX}" "${DISTDIR}/code_3.1.X.${IMAGE_TYPE}.hex"
	
	
	
	
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
