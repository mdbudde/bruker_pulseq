// parsemr_wrapper.cpp

#include "ExternalSequence.h"
#include "pulseq_wrapper.h"
//#include <cstdint>
#include <stdint.h>
#include <string>
#include <ctime>


extern "C" {



ExternalSequenceHandle ExternalSequence_create() {
    return new ExternalSequence();
}

int ExternalSequence_load(ExternalSequenceHandle handle, const char* path) {
    return static_cast<ExternalSequence*>(handle)->load(std::string(path)) ? 1 : 0;
}

void ExternalSequence_destroy(ExternalSequenceHandle handle) {
    delete static_cast<ExternalSequence*>(handle);
}

void Seq_getFOV(ExternalSequence* handle, double* fov0, double* fov1, double* fov2) {
    if (!handle || !fov0 || !fov1 || !fov2) return;
    std::vector<double> def = handle->GetDefinition("FOV");
    if (def.size() == 3) {
        *fov0 = def[0];
        *fov1 = def[1];
        *fov2 = def[2];
    }
}

double Seq_getTotalTime(ExternalSequence* handle, double* totaltime) {
    int64_t                  llTotalDuration = 0;
    for (int iB = 0; iB < handle->GetNumberOfBlocks(); ++iB)
    {
        SeqBlock* pBlock = handle->GetBlock(iB);
        llTotalDuration += pBlock->GetDuration();
        delete pBlock;
    }
    *totaltime = (double)(llTotalDuration/1000);
}


int LoadSeqFile(const char* path_seq) {
    std::string path_cpp(path_seq);
    ExternalSequence seq;
    seq.load(path_cpp);
    // Do whatever minimal work you need here, or call another helper class
    return 1;
}

int TranslateSeqToPpg(const char* path_seq, const char* path_ppg) {
    std::string path_cpp(path_seq);
    ExternalSequence seq;
    seq.load(path_cpp);
    // Do whatever minimal work you need here, or call another helper class


    FILE* fp = fopen(path_ppg, "w");
    if (!fp) return 1;

    fprintf(fp, ";method generated ppg file\n");

    /* Write the current time to the ppg file */
    char timebuffer[20];
    std::time_t t = std::time(NULL);
    std::tm tm;
    localtime_r(&t, &tm);
    std::strftime(timebuffer, sizeof(timebuffer), "%Y-%m-%d %H:%M:%S", &tm);
    fprintf(fp, "; %s\n\n",timebuffer);
    
    fprintf(fp, "#include <MRI.include>\n");
    fprintf(fp, "preset off\n\n");
    fprintf(fp, "INIT_DEVICES\n\n");



            // scan through the sequence, get blocks
            int                      nRF             = 0;
            int                      nGradArb        = 0;
            int                      nGradTrap       = 0;
            int                      nGradExtTrap    = 0;
            int                      nLBL            = 0;
            int                      nADC            = 0;
            int                      nSoDe           = 0;
            int64_t                  llTotalDuration = 0;
            LabelStateAndBookkeeping labelStateAndBookkeeping;
            int                      iB;
            for (iB = 0; iB < seq.GetNumberOfBlocks(); ++iB)
            {
                SeqBlock* pBlock = seq.GetBlock(iB);
                // look into the block, unpack content and collect some data or statistics

                fprintf(fp, "   %.3fm \n",pBlock->GetDuration()/1000);

                if (pBlock->isRF())
                {
                    ++nRF;
                }

                // Process each gradient channel
                for (int iChannel = 0; iChannel < NUM_GRADS; iChannel++)
                {
                    if (pBlock->isArbitraryGradient(iChannel))
                    {
                        ++nGradArb;
                    }
                    else if (pBlock->isExtTrapGradient(iChannel))
                    {
                        ++nGradExtTrap;
                    }
                    else if (pBlock->isTrapGradient(iChannel))
                    {
                        ++nGradTrap;
                    }
                }

                // scanning mdh boundaries / m_maxMdhids, part 1 (here we only update current counters)
                if (pBlock->isLabel())
                {
                    ++nLBL;
                    labelStateAndBookkeeping.updateLabelValues(pBlock);
                }
                // Count ADC events
                if (pBlock->isADC())
                {
                    ++nADC;
                    // if (m_nAdcLength == 0)
                    //{
                    //    m_nAdcLength       = pBlock->GetADCEvent().numSamples;
                    //    m_nAdcDwellTime_ns = pBlock->GetADCEvent().dwellTime;
                    //}
                    // scanning mdh boundaries / m_maxMdhids, part 2 (here we actually update max)
                    if (nLBL)
                    {
                        labelStateAndBookkeeping.updateBookkeepingRecordsADC();
                    }
                }

                if (pBlock->isSoftDelay())
                {
                    ++nSoDe;
                }

                llTotalDuration += pBlock->GetDuration();

                // free up the memory
                delete pBlock;
            }


        fprintf(fp, "exit\n\n");
        fclose(fp);




    return 1;
}

}
    