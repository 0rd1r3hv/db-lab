#include "rm_scan.h"

#include "rm_file_handle.h"

/**
 * @brief 初始化file_handle和rid
 *
 * @param file_handle
 */
RmScan::RmScan(const RmFileHandle *file_handle) : file_handle_(file_handle), rid_((Rid){RM_FIRST_RECORD_PAGE, -1}) {
    // Todo:
    // 初始化file_handle和rid（指向第一个存放了记录的位置）
    next();
}

/**
 * @brief 找到文件中下一个存放了记录的位置
 */
void RmScan::next() {
    // Todo:
    // 找到文件中下一个存放了记录的非空闲位置，用rid_来指向这个位置
    int num_records_per_page = file_handle_->file_hdr_.num_records_per_page;
    while(true) {
        RmPageHandle page_handle = file_handle_->fetch_page_handle(rid_.page_no);
        if ((rid_.slot_no = Bitmap::next_bit(true, page_handle.bitmap, num_records_per_page, rid_.slot_no)) < num_records_per_page)
            return;
        rid_.slot_no = -1;
        if (++rid_.page_no >= file_handle_->file_hdr_.num_pages) {
            rid_.page_no = RM_NO_PAGE;
            return;
        }
    }
}

/**
 * @brief ​ 判断是否到达文件末尾
 */
bool RmScan::is_end() const {
    // Todo: 修改返回值
    return rid_.page_no == RM_NO_PAGE;
}

/**
 * @brief RmScan内部存放的rid
 */
Rid RmScan::rid() const {
    // Todo: 修改返回值
    return rid_;
}