#pragma once

#include <cstddef>
#include <memory>
#include <string>
#include <vector>

struct PendingCommand;
class Reporter
{
public:
    virtual void SetConcurrencyCount(size_t count) = 0;
    virtual void SetRunningCommand(size_t channel, PendingCommand *command) = 0;
    virtual void ReportFailure(PendingCommand *command, int error, const std::string &errors) = 0;
    virtual ~Reporter() = default;
    static std::unique_ptr<Reporter> Get(const std::string &name);

protected:
    Reporter() = default;
};

class ConsoleReporter : public Reporter
{
public:
    ConsoleReporter();
    void SetConcurrencyCount(size_t count);
    void SetRunningCommand(size_t channel, PendingCommand *command);
    void ReportFailure(PendingCommand *command, int error, const std::string &errors);

private:
    void Redraw();
    std::vector<PendingCommand *> activeProcesses;
};

class SimpleReporter : public Reporter
{
public:
    void SetConcurrencyCount(size_t count);
    void SetRunningCommand(size_t channel, PendingCommand *command);
    void ReportFailure(PendingCommand *command, int error, const std::string &errors);
};
