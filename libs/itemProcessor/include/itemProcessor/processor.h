#pragma once

#include "itemProcessor_export.h"

#include <memory>
#include <vector>

/* Here I am trying to solve a problem which I encountered at work.
 *
 * We have a device sending "items" to be processed in a sequential fashion, and we do not know exactly the number
 * of items which will arrive (Although we know that they come in batchs of 90-100). As soon, as 1 arrives, we know
 * that a complete batch will come. The consumer of this class, will mark the end of a batch by calling completeSet().
 * Several batchs could arrive over time (different acquisitions from the device).
 *
 * Note that while we are processing one of the items, another one could be sent from the device before the first item
 * is processed. We would need to append that item to a queue, since we cannot process 2 items at the same time.
 *
 * Also, when the user request for the data with the accessor, if the items are not processed at this time, the call
 * will block until the data is available. If the user tries to access the processed items before calling completeSet()
 * the method will throw.
 *
 * Although I do not like the design, what I have at work right now is that we have to call a reset() method before
 * being able to add items.
 */
class ITEMPROCESSOR_EXPORT ItemProcessor {
 public:
  ItemProcessor();
  ~ItemProcessor();

  void reset();
  void addItem(int item);
  void completeSet();

  const std::vector<int>& data() const;

 private:
  struct Pimpl;
  std::unique_ptr<Pimpl> _p;
};
