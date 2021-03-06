//AliAnalysisTaskNetLambdaMCTrad *AddTaskNetLambdaMCTrad( Bool_t lSaveEventTree = kTRUE, Bool_t lSaveV0 = kTRUE, Bool_t lSaveCascade = kTRUE, TString lExtraOptions = "", const TString lMasterJobSessionFlag = "")
AliAnalysisTaskNetLambdaMCTrad *AddTaskNetLambdaMCTrad( Bool_t lSaveEventTree = kTRUE, Bool_t lSaveV0 = kTRUE, TString lExtraOptions = "", const TString lMasterJobSessionFlag = "")

{
    // Creates, configures and attaches to the train a cascades check task.
    // Get the pointer to the existing analysis manager via the static access method.
    //==============================================================================
    AliAnalysisManager *mgr = AliAnalysisManager::GetAnalysisManager();
    if (!mgr) {
        ::Error("AddTaskNetLambdaMCTrad", "No analysis manager to connect to.");
        return NULL;
    }
    
    // Check the analysis type using the event handlers connected to the analysis manager.
    //==============================================================================
    if (!mgr->GetInputEventHandler()) {
        ::Error("AddTaskNetLambdaMCTrad", "This task requires an input event handler");
        return NULL;
    }
    TString type = mgr->GetInputEventHandler()->GetDataType(); // can be "ESD" or "AOD"
    
    // Create and configure the task
    AliAnalysisTaskNetLambdaMCTrad *task = new AliAnalysisTaskNetLambdaMCTrad(lSaveEventTree, lSaveV0, "task", lExtraOptions);
    mgr->AddTask(task);
    TString outputFileName = AliAnalysisManager::GetCommonFileName();
    
//    outputFileName += ":PWGLF_StrVsMult";
//    if (mgr->GetMCtruthEventHandler()) outputFileName += "_MC";
    
    outputFileName = "Netlambdaresults.root";
//    Printf("Set OutputFileName : \n %s\n", outputFileName.Data() );
    
    AliAnalysisDataContainer *coutputList = mgr->CreateContainer("cList",
                                                                 TList::Class(),
                                                                 AliAnalysisManager::kOutputContainer,
                                                                 outputFileName );
//    AliAnalysisDataContainer *coutputListV0 = mgr->CreateContainer("cListV0",
//                                                                 TList::Class(),
//                                                                 AliAnalysisManager::kOutputContainer,
//                                                                 outputFileName );
//    AliAnalysisDataContainer *coutputListCascade = mgr->CreateContainer("cListCascade",
//                                                                 TList::Class(),
//                                                                 AliAnalysisManager::kOutputContainer,
//                                                                 outputFileName );
//    if( lSaveEventTree ){
//        AliAnalysisDataContainer *coutputTree = mgr->CreateContainer("cTreeEvent",
//                                                                     TTree::Class(),
//                                                                     AliAnalysisManager::kOutputContainer,
//                                                                     outputFileName );
//        coutputTree->SetSpecialOutput();
//    }
//    if( lSaveV0 ){
//        AliAnalysisDataContainer *coutputTreeV0 = mgr->CreateContainer("cTreeV0",
//                                                                       TTree::Class(),
//                                                                       AliAnalysisManager::kOutputContainer,
//                                                                       outputFileName );
//        coutputTreeV0->SetSpecialOutput();
//    }
//    if (lSaveCascade){
//        AliAnalysisDataContainer *coutputTreeCascade = mgr->CreateContainer("cTreeCascade",
//                                                                            TTree::Class(),
//                                                                            AliAnalysisManager::kOutputContainer,
//                                                                            outputFileName );
//        coutputTreeCascade->SetSpecialOutput();
//    }
    //This one you should merge in file-resident ways...
    
    //Recommendation: Tree as a single output slot
    mgr->ConnectInput (task, 0, mgr->GetCommonInputContainer());
    mgr->ConnectOutput(task, 1, coutputList);
//    mgr->ConnectOutput(task, 2, coutputListV0);
//    mgr->ConnectOutput(task, 3, coutputListCascade);
//
//    if ( lSaveEventTree ) mgr->ConnectOutput(task, 4, coutputTree);
//    if ( lSaveV0 )        mgr->ConnectOutput(task, 5, coutputTreeV0);
//    if ( lSaveCascade )   mgr->ConnectOutput(task, 6, coutputTreeCascade);
    
    return task;
}   
